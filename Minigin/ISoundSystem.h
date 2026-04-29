#pragma once

namespace dae
{
	class ISoundSystem
	{
	public:
		virtual ~ISoundSystem() = default;
		virtual void Play() = 0;
	};
}