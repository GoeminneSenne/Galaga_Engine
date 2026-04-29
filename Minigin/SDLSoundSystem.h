#pragma once
#include "ISoundSystem.h"

namespace dae
{
	class SDLSoundSystem : public ISoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem() override = default;
		void Play() override;
	};
}
