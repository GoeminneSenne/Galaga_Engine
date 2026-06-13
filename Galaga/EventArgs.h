#pragma once
#include <Event.h>

namespace galaga
{
	struct ButtonClickedArgs : public dae::EventArgs
	{
		explicit ButtonClickedArgs(const std::string& buttonName) : buttonName(buttonName) {}

		std::string buttonName{};
	};
}