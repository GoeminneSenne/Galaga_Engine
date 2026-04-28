#include "ServiceLocator.h"

dae::ISoundSystem& dae::ServiceLocator::GetSoundSystem()
{
	return *m_soundSystem;
}

void dae::ServiceLocator::RegisterSoundSystem(std::unique_ptr<ISoundSystem> soundSystem)
{
	m_soundSystem = std::move(soundSystem);
}
