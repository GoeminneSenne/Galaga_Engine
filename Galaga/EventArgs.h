#pragma once
#include <Event.h>

namespace galaga
{
	struct ButtonClickedArgs : public dae::EventArgs
	{
		explicit ButtonClickedArgs(const std::string& buttonName) : buttonName(buttonName) {}

		std::string buttonName{};
	};

	struct EnemyDestroyedArgs : public dae::EventArgs
	{
		explicit EnemyDestroyedArgs(int score) : score(score) {}

		int score;
	};
}