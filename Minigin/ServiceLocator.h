#pragma once
#include <memory>

#include "ISoundSystem.h"

namespace dae
{
	class ServiceLocator final
	{
	public:
		static ISoundSystem& GetSoundSystem();
		static void RegisterSoundSystem(std::unique_ptr<ISoundSystem> soundSystem);

	private:
		static std::unique_ptr<ISoundSystem> m_soundSystem;
	};
}