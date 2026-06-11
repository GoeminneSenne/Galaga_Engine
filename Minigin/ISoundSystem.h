#pragma once
#include <string>

#include "IEventListener.h"

namespace dae
{
	class ISoundSystem
	{
	public:
		ISoundSystem() = default;
		virtual ~ISoundSystem() = default;

		virtual void PlaySFX(const std::string& path) = 0;
	};
}
