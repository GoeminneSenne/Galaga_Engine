#include "Health.h"

dae::Health::Health(GameObject* pOwner, int numLives)
	: Component{ pOwner }, m_numLives{ numLives }
{}

void dae::Health::Damage()
{
	--m_numLives;
}
