#include "Health.h"

dae::Health::Health(GameObject* pOwner, int numLives)
	: Component{ pOwner }, m_numLives{ numLives }, m_pSubject{std::make_unique<Subject>()}
{}

dae::Subject* dae::Health::GetSubject() const
{
	return m_pSubject.get();
}

int dae::Health::GetNumLives() const
{
	return m_numLives;
}

void dae::Health::Damage()
{
	--m_numLives;
	m_pSubject->NotifyObservers(make_sdbm_hash("PlayerDied"), GetOwner());
}
