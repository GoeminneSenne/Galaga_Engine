#pragma once
#include "ISoundSystem.h"

namespace dae
{
	class NullSoundSystem : ISoundSystem
	{
	public:
		~NullSoundSystem() override = default;
		void Play() override;
	};
}
