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
#include "Commands/AddScoreCommand.h"
#include "Commands/MoveObjectCommand.h"
#include "Components/HealthDisplay.h"
#include "Components/Score.h"
#include "Components/ScoreDisplay.h"

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

	///CONTROLS 1
	////////////////////////////////////////////
	go = std::make_unique<dae::GameObject>();
	go->GetTransform()->SetLocalPosition(10, 100);
	go->AddComponent<dae::TextureRenderer>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	go->AddComponent<dae::TextComponent>("Use WASD to move Bird, C to inflict damage, Z and X to kill ships", font);
	scene.Add(std::move(go));
	///////////////////////////////////////////

	///SHIP 1
	/////////////////////////////////////////////////////////
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureRenderer>("Galaga/ship1.png");
	go->GetTransform()->SetLocalPosition(500, 400);
	auto pHealth = go->AddComponent<dae::Health>(3);
	auto pScore = go->AddComponent<dae::Score>();

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
	auto asc = std::make_unique<dae::AddScoreCommand>(pScore, 10);
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_Z, dae::KeyState::Down, std::move(asc));
	asc = std::make_unique<dae::AddScoreCommand>(pScore, 100);
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_X, dae::KeyState::Down, std::move(asc));

	scene.Add(std::move(go));
	////////////////////////////////////////////////////////////

	///HealthDisplay 1
	/////////////////////////////////////////////////////////////
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureRenderer>();
	go->AddComponent<dae::TextComponent>("Yeey", font);
	auto healthDisplay = go->AddComponent<dae::HealthDisplay>(pHealth);
	go->GetTransform()->SetLocalPosition(10, 150);
	pHealth->GetSubject()->AddObserver(healthDisplay);

	scene.Add(std::move(go));
	/////////////////////////////////////////////////////////////

	///ScoreDisplay 1
	////////////////////////////////////////////////////////////
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureRenderer>();
	go->AddComponent<dae::TextComponent>("Score: 0", font);
	auto scoreDisplay = go->AddComponent<dae::ScoreDisplay>();
	go->GetTransform()->SetLocalPosition(10, 170);
	pScore->GetSubject()->AddObserver(scoreDisplay);

	scene.Add(std::move(go));
	////////////////////////////////////////////////////////////

	///CONTROLS 2
	////////////////////////////////////////////
	go = std::make_unique<dae::GameObject>();
	go->GetTransform()->SetLocalPosition(10, 118);
	go->AddComponent<dae::TextureRenderer>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	go->AddComponent<dae::TextComponent>("Use Arrow keys to move Ship, I to inflict damage, O and P to kill ships", font);
	scene.Add(std::move(go));
	///////////////////////////////////////////

	///SHIP 2
	/////////////////////////////////////////////////////////////
	go = std::make_unique<dae::GameObject>();
	//child->SetParent(go.get());
	go->GetTransform()->SetLocalPosition(400, 310);
	go->AddComponent<dae::TextureRenderer>("Galaga/ship2.png");
	pHealth = go->AddComponent<dae::Health>(3);
	pScore = go->AddComponent<dae::Score>();

	/*
	moc = std::make_unique<dae::MoveObjectCommand>(go.get(), glm::vec3(1, 0, 0), 100.f);
	dae::InputManager::GetInstance().AddButtonbind(dae::GamepadButton::DPAD_RIGHT, 0, dae::KeyState::Pressed, std::move(moc));
	moc = std::make_unique<dae::MoveObjectCommand>(go.get(), glm::vec3(-1, 0, 0), 100.f);
	dae::InputManager::GetInstance().AddButtonbind(dae::GamepadButton::DPAD_LEFT, 0, dae::KeyState::Pressed, std::move(moc));
	moc = std::make_unique<dae::MoveObjectCommand>(go.get(), glm::vec3(0, -1, 0), 100.f);
	dae::InputManager::GetInstance().AddButtonbind(dae::GamepadButton::DPAD_UP, 0, dae::KeyState::Pressed, std::move(moc));
	moc = std::make_unique<dae::MoveObjectCommand>(go.get(), glm::vec3(0, 1, 0), 100.f);
	dae::InputManager::GetInstance().AddButtonbind(dae::GamepadButton::DPAD_DOWN, 0, dae::KeyState::Pressed, std::move(moc));
	*/
	moc = std::make_unique<dae::MoveObjectCommand>(go.get(), glm::vec3(1, 0, 0), 50.f);
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_RIGHT, dae::KeyState::Pressed, std::move(moc));
	moc = std::make_unique<dae::MoveObjectCommand>(go.get(), glm::vec3(-1, 0, 0), 50.f);
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_LEFT, dae::KeyState::Pressed, std::move(moc));
	moc = std::make_unique<dae::MoveObjectCommand>(go.get(), glm::vec3(0, -1, 0), 50.f);
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_UP, dae::KeyState::Pressed, std::move(moc));
	moc = std::make_unique<dae::MoveObjectCommand>(go.get(), glm::vec3(0, 1, 0), 50.f);
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_DOWN, dae::KeyState::Pressed, std::move(moc));

	dc = std::make_unique<dae::DamageCommand>(pHealth);
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_I, dae::KeyState::Down, std::move(dc));
	asc = std::make_unique<dae::AddScoreCommand>(pScore, 10);
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_O, dae::KeyState::Down, std::move(asc));
	asc = std::make_unique<dae::AddScoreCommand>(pScore, 100);
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_P, dae::KeyState::Down, std::move(asc));

	scene.Add(std::move(go));
	///////////////////////////////////////////////////////////

	///HealthDisplay 2
	/////////////////////////////////////////////////////////////
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureRenderer>();
	go->AddComponent<dae::TextComponent>("Yeey", font);
	healthDisplay = go->AddComponent<dae::HealthDisplay>(pHealth);
	go->GetTransform()->SetLocalPosition(10, 200);
	pHealth->GetSubject()->AddObserver(healthDisplay);

	scene.Add(std::move(go));
	/////////////////////////////////////////////////////////////

	///ScoreDisplay 2
	////////////////////////////////////////////////////////////
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureRenderer>();
	go->AddComponent<dae::TextComponent>("Score: 0", font);
	scoreDisplay = go->AddComponent<dae::ScoreDisplay>();
	go->GetTransform()->SetLocalPosition(10, 220);
	pScore->GetSubject()->AddObserver(scoreDisplay);

	scene.Add(std::move(go));
	////////////////////////////////////////////////////////////
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
