#pragma once
#include <memory>

#include "glm/vec3.hpp"

namespace galaga
{
	class EnemyComponent;

	class EnemyState
	{
	public:
		virtual ~EnemyState() = default;
		virtual std::unique_ptr<EnemyState> Update(float, EnemyComponent*) { return nullptr; }
		virtual void OnEnter(EnemyComponent*) {}
		virtual void OnExit(EnemyComponent*) {}
	};

	class EntryState : public EnemyState
	{
	public:
		std::unique_ptr<EnemyState> Update(float deltaTime, EnemyComponent* enemy) override;
		void OnEnter(EnemyComponent*) override;

	private:
		glm::vec3 m_speed{ 20 };
		glm::vec3 m_moveDirection{};
	};
}
