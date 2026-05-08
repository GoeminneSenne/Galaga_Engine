#include "EnemyState.h"

#include "EnemyComponent.h"
#include "glm/ext/quaternion_geometric.hpp"

std::unique_ptr<galaga::EnemyState> galaga::EntryState::Update(float deltaTime, EnemyComponent* enemy)
{
	enemy->Move(m_moveDirection * m_speed * deltaTime);
	if (glm::distance(enemy->GetWorldPosition(), enemy->GetFormationPosition()) <= 1.f)
	{
		return std::make_unique<IdleState>();
	}
	
	return nullptr;
}

void galaga::EntryState::OnEnter(EnemyComponent* enemyComponent)
{
	glm::vec3 startPos{ enemyComponent->GetWorldPosition() };
	glm::vec3 formationPos{ enemyComponent->GetFormationPosition() };

	m_moveDirection = glm::normalize(formationPos - startPos);
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
