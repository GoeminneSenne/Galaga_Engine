#include "EnemyState.h"

#include "EnemyComponent.h"
#include "glm/ext/quaternion_geometric.hpp"

std::unique_ptr<galaga::EnemyState> galaga::EntryState::Update(float deltaTime, EnemyComponent* enemy)
{
	enemy->Move(m_moveDirection * m_speed * deltaTime);
	if (glm::distance(enemy->GetWorldPosition(), enemy->GetFormationPosition()) <= 0.1f)
	{
		assert(false);
		//Return other state.
	}
	
	return nullptr;
}

void galaga::EntryState::OnEnter(EnemyComponent* enemyComponent)
{
	glm::vec3 startPos{ enemyComponent->GetWorldPosition() };
	glm::vec3 formationPos{ enemyComponent->GetFormationPosition() };

	m_moveDirection = glm::normalize(formationPos - startPos);
}
