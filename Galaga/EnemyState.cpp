#include "EnemyState.h"

#include <algorithm>

#include "EnemyComponent.h"
#include "GameObject.h"
#include "Window.h"
#include "glm/glm.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/gtc/constants.hpp"


galaga::EntryState::EntryState(const glm::vec3& formationPos)
	:m_targetPos(formationPos)
{}

void galaga::EntryState::OnEnter(EnemyComponent* pEnemy)
{
	m_startPos = pEnemy->GetOwner()->GetTransform()->GetLocalPosition();
}

std::unique_ptr<galaga::EnemyState> galaga::EntryState::Update(float deltaTime, EnemyComponent* pEnemy)
{
	m_elapsed += deltaTime * m_speed;

	glm::vec3 pos = glm::mix(m_startPos, m_targetPos, m_elapsed);

	if (glm::length(pos - m_targetPos) < 2.f)
	{
		pEnemy->GetOwner()->GetTransform()->SetLocalPosition(m_targetPos);
		return std::make_unique<IdleState>();
	}
	else
	{
		pEnemy->GetOwner()->GetTransform()->SetLocalPosition(pos);
	}
	

	return nullptr;
}

galaga::EntryMovementState::EntryMovementState(const glm::vec3& targetPos, const glm::vec3& loopPos)
	: m_targetPos(targetPos), m_loopPoint(loopPos)
{
	float centerX = float(dae::Window::GetInstance().GetWidth()) / 2.f;
	if (loopPos.x < centerX)
	{
		m_loopCCW = true;
		m_angularSpeed *= -1;
	}

}

std::unique_ptr<galaga::EnemyState> galaga::EntryMovementState::Update(float deltaTime, EnemyComponent* pEnemy)
{

	switch (m_phase)
	{
	case Phase::MoveToLoop:
		MoveToLoop(deltaTime, pEnemy);
		break;
	case Phase::Loop:
		Loop(deltaTime, pEnemy);
		break;
	case Phase::MoveToTarget:
		if (MoveToTarget(deltaTime, pEnemy))
			return std::make_unique<IdleState>();
		break;
	}

	return nullptr;
}

void galaga::EntryMovementState::OnEnter(EnemyComponent* enemyComponent)
{
	m_startPos = enemyComponent->GetWorldPosition();
}

void galaga::EntryMovementState::MoveToLoop(float deltaTime, EnemyComponent* pEnemy)
{
	m_elapsed += deltaTime * m_entrySpeed;
	m_elapsed = std::clamp(m_elapsed, 0.f, 1.f);

	glm::vec3 pos = glm::mix(m_startPos, m_loopPoint, m_elapsed);

	pEnemy->GetOwner()->GetTransform()->SetLocalPosition(pos);

	if (glm::length(pos - m_loopPoint) < m_radius)
	{
		m_phase = Phase::Loop;
		m_elapsed = 0.f;

		auto offset = pos - m_loopPoint;
		m_angle = std::atan2(offset.y, offset.x);
	}
	
}

void galaga::EntryMovementState::Loop(float deltaTime, EnemyComponent* pEnemy)
{
	float delta = m_angularSpeed * deltaTime;
	m_angle += delta;
	//accumulatedAngle += std::abs(delta);

	glm::vec3 pos{};
	pos.x = m_loopPoint.x + cos(m_angle) * m_radius;
	pos.y = m_loopPoint.y + sin(m_angle) * m_radius;

	m_elapsed += deltaTime;

	pEnemy->GetOwner()->GetTransform()->SetLocalPosition(pos);

	//Have a minimum accumulated angle so it still has a loop
	//if (accumulatedAngle >= glm::pi<float>() && ((!loopCCW && angle >= glm::pi<float>()) || (loopCCW && angle <= -glm::two_pi<float>())))
	if (((!m_loopCCW && m_angle >= glm::pi<float>()) || (m_loopCCW && m_angle <= -glm::two_pi<float>())))
	{
		m_phase = Phase::MoveToTarget;
		m_elapsed = 0.f;
		m_loopPoint = pos; //not ideal
	}
}

bool galaga::EntryMovementState::MoveToTarget(float deltaTime, EnemyComponent* pEnemy)
{
	m_elapsed += deltaTime * m_entrySpeed;
	m_elapsed = std::clamp(m_elapsed, 0.f, 1.f);

	glm::vec3 pos = glm::mix(m_loopPoint, m_targetPos, m_elapsed);

	pEnemy->GetOwner()->GetTransform()->SetLocalPosition(pos);

	if (glm::length(pos - m_targetPos) < 1.f)
	{
		return true;
	}

	return false;
}

std::unique_ptr<galaga::EnemyState> galaga::IdleState::Update(float deltaTime, EnemyComponent*)
{
	m_waitTime -= deltaTime;

	if (m_waitTime <= 0.f)
	{
		return std::make_unique<BombingRunState>();
	}

	return nullptr;
}
