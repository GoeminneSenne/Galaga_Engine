#include "SDLSoundSystem.h"

#include <iostream>
#include <SDL3_mixer/SDL_mixer.h>
#include "EventQueue.h"
#include <thread>


dae::SDLSoundSystem::SDLSoundSystem()
	: ISoundSystem()
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

	m_audioThread = std::jthread(&SDLSoundSystem::ProcessAudio, this);
}

dae::SDLSoundSystem::~SDLSoundSystem()
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

void dae::SDLSoundSystem::PlaySFX(const std::string& path)
{

	std::unique_lock<std::mutex> lock(m_mutex);
	m_queue.emplace(SoundEvent{ path, 0 });
	m_conditionVar.notify_one();

	/*
	MIX_Audio* audio = MIX_LoadAudio(m_mixer, path.c_str(), false);
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
	MIX_PlayTrack(track, 0);
	*/
}

void dae::SDLSoundSystem::ProcessAudio()
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

void dae::SDLSoundSystem::ProcessPlaySFX(const SoundEvent& event)
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
	MIX_PlayTrack(track, 0);
}
