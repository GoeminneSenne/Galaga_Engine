#include "FormationManager.h"

#include <fstream>

#include "Collider.h"
#include "EnemyComponent.h"
#include "SceneManager.h"
#include "TextureRenderer.h"
#include "Window.h"

galaga::EnemyType::EnemyType(const SDL_FRect& srcRect, float formationScore, float divingScore, int health)
	: m_srcRect(srcRect), m_formationScore(formationScore), m_divingScore(divingScore), m_health(health){}

const SDL_FRect& galaga::EnemyType::GetSourceRect() const
{
	return m_srcRect;
}

float galaga::EnemyType::GetFormationScore() const
{
	return m_formationScore;
}

float galaga::EnemyType::GetDivingScore() const
{
	return m_divingScore;
}

int galaga::EnemyType::GetHealth() const
{
	return m_health;
}

void galaga::FormationManager::Init()
{
	m_spawnPos = glm::vec3{ (float)dae::Window::GetInstance().GetWidth() / 2.f, 0.f, 0.f};

	LoadWave("Data/Wave1.txt");
	SpawnEnemies();
}

std::unique_ptr<dae::GameObject> galaga::FormationManager::CreateBee(const glm::vec3& formationPos)
{
	return CreateEnemy(formationPos, &m_beeType);
}

std::unique_ptr<dae::GameObject> galaga::FormationManager::CreateButterfly(const glm::vec3&)
{
	return CreateEnemy(glm::vec3{350.f, 50.f, 0.f}, &m_butterflyType);
}

std::unique_ptr<dae::GameObject> galaga::FormationManager::CreateEnemy(const glm::vec3& targetPos, EnemyType* pType)
{
	auto go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureRenderer>("Galaga2.png");
	go->GetTransform()->SetLocalPosition(m_spawnPos);


	go->AddComponent<EnemyComponent>(targetPos, pType);
	go->AddComponent<dae::Collider>(32.f, 32.f);

	return std::move(go);
}

void galaga::FormationManager::LoadWave(const std::string& file)
{
	std::ifstream input(file);

	if (!input.is_open()) return;

	constexpr static float startX{ 100.f };

	glm::vec3 formationPos{ startX, 32.f, 0.f };
	constexpr static float enemySize{ 32.f };

	std::string line{};

	while (std::getline(input, line))
	{
		for (int idx{}; idx < (int)line.size(); ++idx)
		{
			if (line[idx] != '.')
			{
				m_formationEntries.emplace_back(line[idx], formationPos);
			}

			formationPos.x += enemySize;
		}
		
		formationPos.x = startX;
		formationPos.y += enemySize;
	}

	input.close();
}

void galaga::FormationManager::SpawnEnemies()
{
	const auto& scene = dae::SceneManager::GetInstance().GetCurrentScene();

	for (const auto& entry : m_formationEntries)
	{
		if (entry.enemyType == 'Z')
		{
			auto z = CreateBee(entry.formationPos);
			scene->Add(std::move(z));
		}
	}
}
