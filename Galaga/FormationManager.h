#pragma once
#include "GameObject.h"
#include "Singleton.h"
#include "SDL3/SDL_rect.h"

namespace galaga
{
	class EnemyType
	{
	public:
		EnemyType(const SDL_FRect& srcRect, float formationScore, float divingScore, int health);

		const SDL_FRect& GetSourceRect() const;
		float GetFormationScore() const;
		float GetDivingScore() const;
		int GetHealth() const;

	private:
		SDL_FRect m_srcRect{};
		float m_formationScore{};
		float m_divingScore{};
		int m_health{};
	};

	class FormationManager final : public dae::Singleton<FormationManager>
	{
	public:
		void Init();

		std::unique_ptr<dae::GameObject> CreateBee(const glm::vec3& pos);
		std::unique_ptr < dae::GameObject> CreateButterfly(const glm::vec3& pos);
		std::unique_ptr<dae::GameObject> CreateEnemy(const glm::vec3& targetPos, EnemyType* pType);

	private:
		glm::vec3 m_spawnPos{};

		//Enemy Types
		EnemyType m_beeType{ SDL_FRect{145.f, 19.f, 16.f, 16.f}, 50.f, 100.f, 1 };
		EnemyType m_butterflyType{ SDL_FRect{145.f, 55.f, 16.f, 16.f}, 80.f, 160.f, 1 };
	};
}
