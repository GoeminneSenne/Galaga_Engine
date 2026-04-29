#pragma once
#include <mutex>
#include <queue>
#include <string>

#include "ISoundSystem.h"
#include "SDL3_mixer/SDL_mixer.h"

namespace dae
{
	class SDLSoundSystem : public ISoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem() override;

		void PlaySFX(const std::string& path) override;
		void HandleEvent(const Event& event) override;

		void ProcessAudio();

	private:
		MIX_Mixer* m_mixer = nullptr;

		//TODO replace by event content for other events
		std::queue<std::string> m_audioArgs;
		std::mutex m_mutex;
		std::condition_variable m_conditionVar;
		std::jthread m_audioThread;

		bool m_isRunning{ true };
	};
}
