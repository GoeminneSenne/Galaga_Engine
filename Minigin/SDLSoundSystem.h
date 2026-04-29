#pragma once
#include "ISoundSystem.h"
#include "SDL3_mixer/SDL_mixer.h"

namespace dae
{
	class SDLSoundSystem : public ISoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem() override = default;
		void Play() override;
	
	private:
		MIX_Mixer* m_mixer = nullptr;
	};
}
