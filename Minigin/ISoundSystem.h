#pragma once
#include <string>

namespace dae
{
	class ISoundSystem
	{
	public:
		virtual ~ISoundSystem() = default;

		virtual void PlaySFX(const std::string& path) = 0;
	};
}
