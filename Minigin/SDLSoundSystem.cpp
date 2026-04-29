#include "SDLSoundSystem.h"

#include <iostream>
#include <SDL3_mixer/SDL_mixer.h>


dae::SDLSoundSystem::SDLSoundSystem()
{
	//TODO init, ipv constructor
	if (!MIX_Init())
	{
		std::cout << "Mixer error: " << SDL_GetError() << "\n";
		throw std::runtime_error(std::string("Mixer Error: ") + SDL_GetError());
	}

	MIX_Mixer* mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
	if (!mixer)
	{
		std::cout << "Create Mixer Device error: " << SDL_GetError() << "\n";
		throw std::runtime_error(std::string("Create Mixer Device error: ") + SDL_GetError());
	}

	const char* path = "./Data/PlayerShoot.mp3";
	MIX_Audio* audio = MIX_LoadAudio(mixer, path, false);
	if (!audio)
	{
		throw std::runtime_error("Failed to load audio");
	}

	MIX_Track* track = MIX_CreateTrack(mixer);
	MIX_SetTrackAudio(track, audio);
	MIX_PlayTrack(track, 0);
}

void dae::SDLSoundSystem::Play()
{

}
