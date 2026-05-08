#include "EnemyComponent.h"

#include "EnemyState.h"
#include "GameObject.h"

galaga::EnemyComponent::EnemyComponent(dae::GameObject* pOwner, glm::vec3 formationPos)
	: Component(pOwner)
	, m_formationPosition(formationPos)
	, m_state(std::make_unique<EntryState>())
{
	m_state->OnEnter(this);
}

void galaga::EnemyComponent::Update(float deltaTime)
{
	auto newState{ m_state->Update(deltaTime, this) };
	if (newState)
	{
		m_state->OnExit(this);
		m_state = std::move(newState);
		m_state->OnEnter(this);
	}
}

void galaga::EnemyComponent::Move(const glm::vec3& movement)
{
	glm::vec3 pos = GetOwner()->GetTransform()->GetLocalPosition();
	pos += movement;
	GetOwner()->GetTransform()->SetLocalPosition(pos);
}

glm::vec3 galaga::EnemyComponent::GetWorldPosition() const
{
	return GetOwner()->GetTransform()->GetWorldPosition();
}

glm::vec3 galaga::EnemyComponent::GetFormationPosition() const
{
	return m_formationPosition;
}
