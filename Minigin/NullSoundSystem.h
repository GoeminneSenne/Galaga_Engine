#pragma once
#include "ISoundSystem.h"

namespace dae
{
	class NullSoundSystem : public ISoundSystem
	{
	public:
		NullSoundSystem();
		~NullSoundSystem() override = default;
		void Play() override;
	};
}
