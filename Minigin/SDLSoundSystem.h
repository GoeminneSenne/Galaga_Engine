#pragma once
#include <string>
#include "ISoundSystem.h"

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
		void PlaySFX(const std::string& path, float volume) override;

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
