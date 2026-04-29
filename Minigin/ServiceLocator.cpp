#include "ServiceLocator.h"

#include "NullSoundSystem.h"

std::unique_ptr<dae::ISoundSystem> dae::ServiceLocator::m_soundSystem{std::make_unique<NullSoundSystem>()};

dae::ISoundSystem& dae::ServiceLocator::GetSoundSystem()
{
	return *m_soundSystem;
}

void dae::ServiceLocator::RegisterSoundSystem(std::unique_ptr<ISoundSystem> soundSystem)
{

	if (soundSystem)
	{
		m_soundSystem = std::move(soundSystem);
	}
	else
	{
		m_soundSystem = std::make_unique<NullSoundSystem>();
	}
}
