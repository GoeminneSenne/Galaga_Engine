#pragma once
#include "Singleton.h"

namespace galaga
{
	//TODO als geen members op einde, veranderen in nog een namespace
	class SceneCreator : public dae::Singleton<SceneCreator>
	{
	public:
		void CreateGameScene();
		void CreateMainMenu();
	};
}
