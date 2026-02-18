#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Components/FPS.h"
#include "Components/TextRenderer.h"
#include "Components/TextureRenderer.h"
#include "Scene.h"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	auto go = std::make_unique<dae::GameObject>();
	auto textureRenderer = std::make_unique<dae::TextureRenderer>(go.get(), "background.png");
	go->AddComponent(std::move(textureRenderer));
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	textureRenderer = std::make_unique<dae::TextureRenderer>(go.get(), "logo.png");
	go->AddComponent(std::move(textureRenderer));
	go->SetPosition(358, 180);
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textRenderer = std::make_unique<dae::TextRenderer>(go.get(), "Programming 4 Assignment", font);
	textRenderer->SetColor({ 255, 255, 0, 255 });
	go->SetPosition(292, 20);
	go->AddComponent(std::move(textRenderer));
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	textRenderer = std::make_unique<dae::TextRenderer>(go.get(), "100000 FPS", font);
	go->AddComponent(std::move(textRenderer));
	go->SetPosition(20, 20);
	auto fpsc = std::make_unique<dae::FPS>(go.get());
	go->AddComponent(std::move(fpsc));
	scene.Add(std::move(go));
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
