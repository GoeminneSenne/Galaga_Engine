#pragma once
#include <memory>

#include "Component.h"
#include "EnemyState.h"
#include "glm/vec3.hpp"

namespace galaga
{
	class EnemyType;

	class EnemyComponent : public dae::Component
	{
	public:
		explicit EnemyComponent(dae::GameObject* pOwner, glm::vec3 formationPos, EnemyType* pType);
		~EnemyComponent() override = default;

		void Update(float deltaTime) override;
		void OnCollision(dae::GameObject* other) override;

		void Move(const glm::vec3& movement);
		glm::vec3 GetWorldPosition() const;
		glm::vec3 GetFormationPosition() const;
	private:
		glm::vec3 m_formationPosition{};
		std::unique_ptr<EnemyState> m_state{};
		EnemyType* m_pType{};
	};
}
