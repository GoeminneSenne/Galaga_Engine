#pragma once

#include "Singleton.h"

namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:

	private:
		friend class Singleton<Time>;
		Time() = default;


	};
}