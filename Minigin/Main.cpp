#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"

#include "Components/FPS.h"
#include "Components/TextComponent.h"
#include "Components/TextureRenderer.h"
#include "Components/Orbit.h"
#include "Components/CacheGraph.h"
#include "Components/CacheGraphEx2.h"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	auto go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureRenderer>("background.png");
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureRenderer>("logo.png");
	go->GetTransform()->SetLocalPosition(358, 180);
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->GetTransform()->SetLocalPosition(292, 20);
	go->AddComponent<dae::TextureRenderer>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent<dae::TextComponent>("Programming 4 Assignment", font, SDL_Color{255, 255, 0, 255});
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->GetTransform()->SetLocalPosition(20, 20);
	go->AddComponent<dae::TextureRenderer>();
	go->AddComponent<dae::TextComponent>("0 FPS", font);
	go->AddComponent<dae::FPS>();
	scene.Add(std::move(go));

	auto p = std::make_unique<dae::GameObject>();
	p->GetTransform()->SetLocalPosition(400, 400);

	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureRenderer>("Galaga/ship1.png");
	go->AddComponent<dae::Orbit>( 20.f, -10.f);
	go->SetParent(p.get());

	auto child = std::make_unique<dae::GameObject>();
	child->SetParent(go.get());
	child->GetTransform()->SetLocalPosition(10, 10);
	child->AddComponent<dae::TextureRenderer>("Galaga/ship2.png");
	child->AddComponent<dae::Orbit>(30.f, 5.f);

	scene.Add(std::move(p));
	scene.Add(std::move(go));
	scene.Add(std::move(child));

	go = std::make_unique<dae::GameObject>();
	go->GetTransform()->SetLocalPosition(50, 50);
	go->AddComponent<dae::CacheGraph>();
	go->AddComponent<dae::CacheGraphEx2>();

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
