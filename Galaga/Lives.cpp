#include "Lives.h"

#include "EnemyComponent.h"

dae::Lives::Lives(GameObject* pOwner, int numLives)
	: Component{ pOwner }, m_numLives{ numLives }, m_pSubject{std::make_unique<Subject>()}
{}

dae::Subject* dae::Lives::GetSubject() const
{
	return m_pSubject.get();
}

int dae::Lives::GetNumLives() const
{
	return m_numLives;
}

void dae::Lives::Damage()
{
	if (m_isImmortal) return;

	m_isImmortal = true;
	--m_numLives;
	m_pSubject->NotifyObservers(make_sdbm_hash("PlayerDied"), GetOwner());
}

void dae::Lives::Update(float deltaTime)
{
	if (m_isImmortal)
	{
		m_immortalTime += deltaTime;
		if (m_immortalTime >= m_maxImmortalTime)
		{
			m_isImmortal = false;
			m_immortalTime = 0.f;
		}
	}
}

void dae::Lives::OnCollision(GameObject* other)
{
	auto pEnemy = other->GetComponent<galaga::EnemyComponent>();

	if (pEnemy != nullptr)
	{
		Damage();
	}
}
