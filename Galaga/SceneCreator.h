#pragma once
#include "Singleton.h"

namespace galaga
{
	class SceneCreator : public dae::Singleton<SceneCreator>
	{
	public:
		void CreateGameScene();


	};
}
