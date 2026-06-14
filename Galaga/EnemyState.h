#pragma once
#include <memory>

#include "glm/vec3.hpp"
#include "glm/gtc/constants.hpp"

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
		EntryState(const glm::vec3& formationPos);

		void OnEnter(EnemyComponent*) override;
		std::unique_ptr<EnemyState> Update(float deltaTime, EnemyComponent* pEnemy) override;
	private:
		glm::vec3 m_startPos{};
		glm::vec3 m_targetPos{};
		float m_elapsed{};
		constexpr static float m_speed{ .3f };
	};
	
	//Unused
	class EntryMovementState : public EnemyState
	{
	public:
		EntryMovementState(const glm::vec3& targetPos, const glm::vec3& loopPos);

		std::unique_ptr<EnemyState> Update(float deltaTime, EnemyComponent* enemy) override;
		void OnEnter(EnemyComponent*) override;

	private:
		enum class Phase
		{
			MoveToLoop,
			Loop,
			MoveToTarget
		};

		Phase m_phase{};

		float m_angle = 0.f;
		float m_radius = 40.f;
		float m_angularSpeed = 2.f;
		bool m_loopCCW{};

		glm::vec3 m_startPos{};
		glm::vec3 m_targetPos{};
		glm::vec3 m_loopPoint{};

	
		constexpr static float m_entrySpeed{ 0.3f };
		float m_elapsed{};

		void MoveToLoop(float deltaTime, EnemyComponent* pEnemy);
		void Loop(float deltaTime, EnemyComponent* pEnemy);
		bool MoveToTarget(float deltaTime, EnemyComponent* pEnemy);
	};

	class IdleState : public EnemyState
	{
	public:
		std::unique_ptr<EnemyState> Update(float deltaTime, EnemyComponent* enemy) override;

	private:
		float m_waitTime{ 2.f };
	};

	class BombingRunState : public EnemyState
	{
		/*
	public:
		std::unique_ptr<EnemyState> Update(float deltaTime, EnemyComponent* enemy) override;
		void OnEnter(EnemyComponent* enemy) override;

	private:
		glm::vec3 m_attackPos{};
		*/
	};
}
