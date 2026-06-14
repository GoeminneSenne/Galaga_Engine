#include "FormationManager.h"

#include "Collider.h"
#include "EnemyComponent.h"
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
}

std::unique_ptr<dae::GameObject> galaga::FormationManager::CreateBee(const glm::vec3&)
{
	return CreateEnemy(glm::vec3{ 300.f, 50.f, 0.f }, &m_beeType);
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
