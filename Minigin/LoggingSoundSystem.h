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

		void PlaySFX(const std::string& path) override;


	private:
		std::unique_ptr<ISoundSystem> m_realSoundSystem{};
	};

	inline void LoggingSoundSystem::PlaySFX(const std::string& path)
	{
		m_realSoundSystem->PlaySFX(path);
		std::cout << "Playing SFX with path: " << path << "\n";
	}
}
