#include "SDLSoundSystem.h"

#include <SDL3_mixer/SDL_mixer.h>

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

// --- PIMPL ---------------------
class dae::SDLSoundSystem::SDLSoundSystemImpl final
{
public:
	SDLSoundSystemImpl();
	~SDLSoundSystemImpl();

	void PlaySFX(const std::string& path, float volume);
	void ProcessAudio();

private:
	MIX_Mixer* m_mixer = nullptr;
	std::queue<SoundEvent> m_queue;
	std::mutex m_mutex;
	std::condition_variable m_conditionVar;
	std::jthread m_audioThread;
	bool m_isRunning{ true };

	void ProcessPlaySFX(const SoundEvent& event) const;
};

dae::SDLSoundSystem::SDLSoundSystemImpl::SDLSoundSystemImpl()
{
	if (!MIX_Init())
	{
		std::cout << "Mixer error: " << SDL_GetError() << "\n";
		throw std::runtime_error(std::string("Mixer Error: ") + SDL_GetError());
	}

	m_mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
	if (!m_mixer)
	{
		std::cout << "Create Mixer Device error: " << SDL_GetError() << "\n";
		throw std::runtime_error(std::string("Create Mixer Device error: ") + SDL_GetError());
	}

	m_audioThread = std::jthread(&SDLSoundSystemImpl::ProcessAudio, this);
}

dae::SDLSoundSystem::SDLSoundSystemImpl::~SDLSoundSystemImpl()
{
	
	std::unique_lock<std::mutex> lock(m_mutex);
	m_isRunning = false;
	lock.unlock();
	
	m_conditionVar.notify_all();
	
	if (m_audioThread.joinable())
	{
		m_audioThread.join();
	}

}

void dae::SDLSoundSystem::SDLSoundSystemImpl::PlaySFX(const std::string& path, float volume)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_queue.emplace(SoundEvent{ path, volume });
	m_conditionVar.notify_one();
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::ProcessAudio()
{
	while (m_isRunning)
	{
		std::unique_lock<std::mutex> lock(m_mutex);

		m_conditionVar.wait(lock, [&]()
			{ return !m_isRunning || !m_queue.empty(); });

		while (!m_queue.empty())
		{
			auto event = m_queue.front();
			m_queue.pop();

			lock.unlock();
			ProcessPlaySFX(event);
			lock.lock();
		}
	}
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::ProcessPlaySFX(const SoundEvent& event) const
{
	MIX_Audio* audio = MIX_LoadAudio(m_mixer, event.path.c_str(), false);
	if (!audio)
	{
		throw std::runtime_error("Failed to load audio");
	}

	MIX_Track* track = MIX_CreateTrack(m_mixer);
	if (!track)
	{
		throw std::runtime_error("Failed to create track");
	}
	MIX_SetTrackAudio(track, audio);
	MIX_SetTrackGain(track, event.volume);
	MIX_PlayTrack(track, 0);
}


dae::SDLSoundSystem::SDLSoundSystem()
	: ISoundSystem()
	, m_pImpl(std::make_unique<SDLSoundSystemImpl>())
{}

dae::SDLSoundSystem::~SDLSoundSystem() = default;


//TODO: volume toevoegen
void dae::SDLSoundSystem::PlaySFX(const std::string& path, float volume)
{
	m_pImpl->PlaySFX(path, volume);
}

