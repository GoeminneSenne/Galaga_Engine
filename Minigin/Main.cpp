#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Commands/DamageCommand.h"

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
#include "Components/Health.h"

#include <filesystem>

#include "InputManager.h"
#include "Commands/MoveObjectCommand.h"

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

	///FPS COMPONENT
	/////////////////////////////////////////////
	go = std::make_unique<dae::GameObject>();
	go->GetTransform()->SetLocalPosition(10, 10);
	go->AddComponent<dae::TextureRenderer>();
	go->AddComponent<dae::TextComponent>("0 FPS", font);
	go->AddComponent<dae::FPS>();
	scene.Add(std::move(go));
	/////////////////////////////////////////////

	///CONTROLS 2
	////////////////////////////////////////////
	go = std::make_unique<dae::GameObject>();
	go->GetTransform()->SetLocalPosition(10, 100);
	go->AddComponent<dae::TextureRenderer>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	go->AddComponent<dae::TextComponent>("Use WASD to move Bird, C to inflict damage, Z and X to pick up pellets", font);
	scene.Add(std::move(go));
	///////////////////////////////////////////

	///SHIP 1
	/////////////////////////////////////////////////////////
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureRenderer>("Galaga/ship1.png");
	go->GetTransform()->SetLocalPosition(500, 400);
	auto pHealth = go->AddComponent<dae::Health>(2);

	auto moc = std::make_unique<dae::MoveObjectCommand>(go.get(), glm::vec3(1,0,0), 50.f);
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_D, dae::KeyState::Pressed, std::move(moc));
	moc = std::make_unique<dae::MoveObjectCommand>(go.get(), glm::vec3(-1, 0, 0), 50.f);
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_A, dae::KeyState::Pressed, std::move(moc));
	moc = std::make_unique<dae::MoveObjectCommand>(go.get(), glm::vec3(0, -1, 0), 50.f);
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_W, dae::KeyState::Pressed, std::move(moc));
	moc = std::make_unique<dae::MoveObjectCommand>(go.get(), glm::vec3(0, 1, 0), 50.f);
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_S, dae::KeyState::Pressed, std::move(moc));

	auto dc = std::make_unique<dae::DamageCommand>(pHealth);
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_C, dae::KeyState::Down, std::move(dc));

	scene.Add(std::move(go));
	////////////////////////////////////////////////////////////

	///SHIP 2
	/////////////////////////////////////////////////////////////
	go = std::make_unique<dae::GameObject>();
	//child->SetParent(go.get());
	go->GetTransform()->SetLocalPosition(400, 310);
	go->AddComponent<dae::TextureRenderer>("Galaga/ship2.png");

	moc = std::make_unique<dae::MoveObjectCommand>(go.get(), glm::vec3(1, 0, 0), 100.f);
	dae::InputManager::GetInstance().AddButtonbind(dae::GamepadButton::DPAD_RIGHT, 0, dae::KeyState::Pressed, std::move(moc));
	moc = std::make_unique<dae::MoveObjectCommand>(go.get(), glm::vec3(-1, 0, 0), 100.f);
	dae::InputManager::GetInstance().AddButtonbind(dae::GamepadButton::DPAD_LEFT, 0, dae::KeyState::Pressed, std::move(moc));
	moc = std::make_unique<dae::MoveObjectCommand>(go.get(), glm::vec3(0, -1, 0), 100.f);
	dae::InputManager::GetInstance().AddButtonbind(dae::GamepadButton::DPAD_UP, 0, dae::KeyState::Pressed, std::move(moc));
	moc = std::make_unique<dae::MoveObjectCommand>(go.get(), glm::vec3(0, 1, 0), 100.f);
	dae::InputManager::GetInstance().AddButtonbind(dae::GamepadButton::DPAD_DOWN, 0, dae::KeyState::Pressed, std::move(moc));

	scene.Add(std::move(go));
	///////////////////////////////////////////////////////////
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
