#pragma once

namespace dae
{
	class ISoundSystem
	{
		virtual ~ISoundSystem() = default;
		virtual void Play() = 0;
	};
}