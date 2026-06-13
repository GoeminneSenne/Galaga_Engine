#include "SceneCreator.h"

//Engine includes
#include <Minigin.h>
#include <SceneManager.h>
#include <ResourceManager.h>
#include <InputManager.h>
#include <ServiceLocator.h>
#include <Window.h>
#include <TextureRenderer.h>
#include <TextComponent.h>
#include <FPS.h>
#include <Collider.h>

#include "UIButton.h"

#if USE_STEAMWORKS
#include <AchievementObserver.h>
#endif

//Galaga includes
#include "DamageCommand.h"
#include "BackgroundComponent.h"
#include "Score.h"
#include "PlayerShip.h"
#include "MoveObjectCommand.h"
#include "AddScoreCommand.h"
#include "ShootCommand.h"
#include "LivesDisplay.h"
#include "EnemyComponent.h"
#include "MenuComponent.h"

namespace fs = std::filesystem;

void galaga::SceneCreator::CreateGameScene()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	//Background
	////////////////////////////////////////////////
	constexpr float scrollSpeed{ 200.f };
	const float wWidth = float(dae::Window::GetInstance().GetWidth());
	const float wHeight = float(dae::Window::GetInstance().GetHeight());

	auto go = std::make_unique<dae::GameObject>();
	go->GetTransform()->SetLocalPosition(0, 0);
	auto tc = go->AddComponent<dae::TextureRenderer>("background.png");
	tc->SetDestinationSize(wWidth, wHeight);

	go->AddComponent<galaga::BackgroundComponent>(scrollSpeed, wHeight);
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->GetTransform()->SetLocalPosition(0, -wHeight);
	tc = go->AddComponent<dae::TextureRenderer>("background.png");
	tc->SetDestinationSize(wWidth, wHeight);
	go->AddComponent<galaga::BackgroundComponent>(scrollSpeed, wHeight);
	scene.Add(std::move(go));
	////////////////////////////////////////////////

	///FPS COMPONENT
	/////////////////////////////////////////////
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

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
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	//go->AddComponent<dae::TextComponent>("Use WASD to move Bird, C to inflict damage, Z and X to kill ships", font);
	go->AddComponent<dae::TextComponent>("Press Space to fire bullets, Q/D to move", font);
	scene.Add(std::move(go));
	///////////////////////////////////////////

	///SHIP 1
	/////////////////////////////////////////////////////////
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureRenderer>("Galaga.png");
	go->GetTransform()->SetLocalPosition(500, 400);
	auto pLives = go->AddComponent<dae::Lives>(3);
	go->AddComponent<dae::Score>();
	auto pPlayerShip = go->AddComponent<dae::PlayerShip>(0.f, wWidth);
	go->AddComponent<dae::Collider>(32.f, 32.f);

	auto moc = std::make_unique<dae::MoveObjectCommand>(go.get(), glm::vec3(1, 0, 0), 50.f);
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_D, dae::KeyState::Pressed, std::move(moc));
	moc = std::make_unique<dae::MoveObjectCommand>(go.get(), glm::vec3(-1, 0, 0), 50.f);
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_A, dae::KeyState::Pressed, std::move(moc));
	moc = std::make_unique<dae::MoveObjectCommand>(go.get(), glm::vec3(0, -1, 0), 150.f);
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_W, dae::KeyState::Pressed, std::move(moc));

	auto dc = std::make_unique<dae::DamageCommand>(pLives);
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_C, dae::KeyState::Down, std::move(dc));
	auto asc = std::make_unique<dae::AddScoreCommand>(10, go.get());
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_Z, dae::KeyState::Down, std::move(asc));
	asc = std::make_unique<dae::AddScoreCommand>(100, go.get());
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_X, dae::KeyState::Down, std::move(asc));

	auto sc = std::make_unique<dae::ShootCommand>(pPlayerShip);
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_SPACE, dae::KeyState::Down, std::move(sc));

	scene.Add(std::move(go));
	////////////////////////////////////////////////////////////

	///LivesDisplay
	/////////////////////////////////////////////////////////////
	go = std::make_unique<dae::GameObject>();
	auto livesDisplay = go->AddComponent<dae::LivesDisplay>(pLives);
	go->GetTransform()->SetLocalPosition(10, 150);
	pLives->GetSubject()->AddObserver(livesDisplay);

	scene.Add(std::move(go));
	/////////////////////////////////////////////////////////////


	/// Enemy Ship
	//////////////////////////////////////////////////////////
	go = std::make_unique<dae::GameObject>();
	tc = go->AddComponent<dae::TextureRenderer>("Galaga2.png");
	tc->SetSourceRect(145.f, 19.f, 16.f, 16.f);
	tc->SetDestinationSize(32.f, 32.f);
	go->GetTransform()->SetLocalPosition(300, 0);

	go->AddComponent<galaga::EnemyComponent>(glm::vec3{ 300, 300, 0 });
	go->AddComponent<dae::Collider>(32.f, 32.f);

	scene.Add(std::move(go));
	//////////////////////////////////////////////////////////

	//Start Sound Effect
	dae::ServiceLocator::GetSoundSystem().PlaySFX("./Data/Start.mp3", 0.1f);

#if USE_STEAMWORKS
	///Achievements
	////////////////////////////////////
	go = std::make_unique<dae::GameObject>();
	auto achObs = go->AddComponent<dae::AchievementObserver>();

	pScore1->GetSubject()->AddObserver(achObs);
	pScore2->GetSubject()->AddObserver(achObs);

	scene.Add(std::move(go));
	///////////////////////////////////
#endif
}

void galaga::SceneCreator::CreateMainMenu()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	auto go = std::make_unique<dae::GameObject>();
	//go->AddComponent<dae::TextureRenderer>("logo.png");
	go->GetTransform()->SetLocalPosition(50.f, 50.f);
	auto menu = go->AddComponent<MenuComponent>();
	scene.Add(std::move(go));


	//TEst button
	go = std::make_unique<dae::GameObject>();
	go->GetTransform()->SetLocalPosition(50.f, 100.f);
	go->AddComponent<dae::TextureRenderer>("Button.png");
	go->AddComponent<UIButton>(menu, "test");
	scene.Add(std::move(go));
}
