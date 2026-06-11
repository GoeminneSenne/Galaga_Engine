#pragma once
#include <iostream>

#include "ISoundSystem.h"

namespace dae
{
	class LoggingSoundSystem : public ISoundSystem
	{
	public:
		LoggingSoundSystem(std::unique_ptr<ISoundSystem>&& ss) : m_realSoundSystem(std::move(ss)) {}
		~LoggingSoundSystem() override = default;

		void PlaySFX(const std::string& path, float volume) override;


	private:
		std::unique_ptr<ISoundSystem> m_realSoundSystem{};
	};

	inline void LoggingSoundSystem::PlaySFX(const std::string& path, float volume)
	{
		m_realSoundSystem->PlaySFX(path, volume);
		std::cout << "Playing SFX with path: " << path << "\n";
	}
}
