#include "SDLSoundSystem.h"

#include <iostream>
#include <SDL3_mixer/SDL_mixer.h>
#include "EventQueue.h"


dae::SDLSoundSystem::SDLSoundSystem()
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

	EventQueue::GetInstance().Subscribe(make_sdbm_hash("PlaySFX"), this);
}

void dae::SDLSoundSystem::PlaySFX(const std::string& path)
{
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
}

void dae::SDLSoundSystem::HandleEvent(const Event& event)
{
	if (event.id == make_sdbm_hash("PlaySFX"))
	{
		PlaySFX("./Data/PlayerShoot.mp3");
	}
}
