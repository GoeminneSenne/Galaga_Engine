#pragma once
#include <memory>

#include "Component.h"
#include "EnemyState.h"
#include "glm/vec3.hpp"

namespace galaga
{
	class EnemyComponent : public dae::Component
	{
	public:
		explicit EnemyComponent(dae::GameObject* pOwner, glm::vec3 formationPos);
		~EnemyComponent() override = default;

		void Update(float deltaTime) override;

		auto Move(const glm::vec3& movement) -> void;
		glm::vec3 GetWorldPosition() const;
		glm::vec3 GetFormationPosition() const;
	private:
		glm::vec3 m_formationPosition{};
		std::unique_ptr<EnemyState> m_state{};
	};
}
