#include "FormationManager.h"

#include "Collider.h"
#include "EnemyComponent.h"
#include "TextureRenderer.h"

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

std::unique_ptr<dae::GameObject> galaga::FormationManager::CreateBee(const glm::vec3& pos)
{
	auto go = std::make_unique<dae::GameObject>();
	auto tc = go->AddComponent<dae::TextureRenderer>("Galaga2.png");
	tc->SetSourceRect(m_beeType.GetSourceRect());
	tc->SetDestinationSize(32.f, 32.f);
	go->GetTransform()->SetLocalPosition(pos);

	go->AddComponent<EnemyComponent>(glm::vec3{300, 50.f, 0.f}, &m_beeType);
	go->AddComponent<dae::Collider>(32.f, 32.f);

	return std::move(go);
}
