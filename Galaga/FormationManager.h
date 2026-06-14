#pragma once
#include "EnemyComponent.h"
#include "GameObject.h"
#include "Singleton.h"
#include "SDL3/SDL_rect.h"

namespace galaga
{
	struct FormationEntry
	{
		char enemyType;
		glm::vec3 formationPos;
	};

	class EnemyType
	{
	public:
		EnemyType(const SDL_FRect& srcRect, int formationScore, int divingScore, int health);

		const SDL_FRect& GetSourceRect() const;
		int GetFormationScore() const;
		int GetDivingScore() const;
		int GetHealth() const;

	private:
		SDL_FRect m_srcRect{};
		int m_formationScore{};
		int m_divingScore{};
		int m_health{};
	};

	class FormationManager final : public dae::Singleton<FormationManager>
	{
	public:
		void Init();

		std::unique_ptr<dae::GameObject> CreateBee(const glm::vec3& pos);
		std::unique_ptr < dae::GameObject> CreateButterfly(const glm::vec3& pos);
		std::unique_ptr<dae::GameObject> CreateEnemy(const glm::vec3& targetPos, EnemyType* pType);

		void Update(float deltaTime);
		void TriggerBombingRun();

		void RemoveEnemy(EnemyComponent* pEnemy);
		void DecreaseActiveBombers();

		void LoadWave(int currentWave);
		void LoadWave(const std::string& file);
		void SpawnEnemies();

	private:
		glm::vec3 m_spawnPos{};

		std::vector<FormationEntry> m_formationEntries;
		std::vector<EnemyComponent*> m_enemies;
		int m_numEnemiesAlive{};
		int m_numActiveBombers{};
		int m_currentWave{};

		constexpr static int m_numWaves{ 2 };
		
		constexpr static float m_diveCooldown{5.f};
		float m_diveTimer{};

		//Enemy Types
		EnemyType m_beeType{ SDL_FRect{145.f, 19.f, 16.f, 16.f}, 50, 100, 1 };
		EnemyType m_butterflyType{ SDL_FRect{145.f, 55.f, 16.f, 16.f}, 80, 160, 1 };
		EnemyType m_bossType{ SDL_FRect{145.f, 109.f, 16.f, 16.f}, 150, 400, 2 };
	};
}
