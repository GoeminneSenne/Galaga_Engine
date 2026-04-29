#include "NullSoundSystem.h"

dae::NullSoundSystem::NullSoundSystem()
	:ISoundSystem()
{
}

void dae::NullSoundSystem::PlaySFX(const std::string&)
{
}

void dae::NullSoundSystem::HandleEvent(const Event&)
{
}

