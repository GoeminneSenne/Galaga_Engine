#pragma once

#include <vector>
#include "Singleton.h"

namespace dae
{
	class Collider;
	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:
		void AddCollider(Collider* collider);
		void RemoveCollider(Collider* collider);

		void CheckCollisions() const;

	private:
		std::vector<Collider*> m_colliders;
	};
}