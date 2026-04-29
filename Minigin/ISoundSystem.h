#pragma once
#include <string>

#include "IEventListener.h"

namespace dae
{
	class ISoundSystem : public IEventListener
	{
	public:
		ISoundSystem() = default;
		virtual ~ISoundSystem() override = default;

		virtual void PlaySFX(const std::string& path) = 0;
	};
}
