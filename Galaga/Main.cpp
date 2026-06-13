#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include <filesystem>
#include <Minigin.h>

#include "GameStateManager.h"
#include "SceneCreator.h"

namespace fs = std::filesystem;

static void load()
{
	//galaga::SceneCreator::GetInstance().CreateGameScene();
	//galaga::SceneCreator::GetInstance().CreateMainMenu();

	galaga::GameStateManager::GetInstance().Init();
}

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
    return 0;
}
