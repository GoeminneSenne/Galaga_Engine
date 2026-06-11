#pragma once
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#include "ISoundSystem.h"
#include "SDL3_mixer/SDL_mixer.h"

namespace dae
{
	struct SoundEvent
	{
		std::string path{};
		float volume{};
	};

	class SDLSoundSystem : public ISoundSystem
	{
	public:
		void PlaySFX(const std::string& path) override;

		SDLSoundSystem();
		~SDLSoundSystem() override;
		SDLSoundSystem(const SDLSoundSystem&) = delete;
		SDLSoundSystem(SDLSoundSystem&&) = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem&) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&&) = delete;
	private:
		class SDLSoundSystemImpl;
		std::unique_ptr<SDLSoundSystemImpl> m_pImpl;
	};
}
