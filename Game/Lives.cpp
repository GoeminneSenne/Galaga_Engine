#include "Lives.h"

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
	--m_numLives;
	m_pSubject->NotifyObservers(make_sdbm_hash("PlayerDied"), GetOwner());
}
