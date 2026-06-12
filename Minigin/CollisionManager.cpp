#include "CollisionManager.h"

#include <algorithm>

#include "Collider.h"
#include "GameObject.h"

void dae::CollisionManager::AddCollider(Collider* collider)
{
	if (std::ranges::find(m_colliders, collider) != m_colliders.end()) return;

	m_colliders.push_back(collider);
}

void dae::CollisionManager::RemoveCollider(Collider* collider)
{
	auto itr = std::ranges::find(m_colliders, collider);
	if (itr == m_colliders.end()) return;
	m_colliders.erase(itr);
}

void dae::CollisionManager::CheckCollisions() const
{
	for (int idx{}; idx < static_cast<int>(m_colliders.size()); ++idx)
	{
		Collider* currentCollider = m_colliders[idx];

		//Start from current index so we don't have duplicate collisions
		for (int otherIdx{idx + 1}; otherIdx < static_cast<int>(m_colliders.size()); ++otherIdx)
		{
			Collider* otherCollider = m_colliders[otherIdx];

			if (currentCollider->IsColliding(*otherCollider))
			{
				GameObject* currentObj = currentCollider->GetOwner();
				GameObject* otherObj = otherCollider->GetOwner();

				currentObj->OnCollision(otherObj);
				otherObj->OnCollision(currentObj);
			}
		}
	}
}

