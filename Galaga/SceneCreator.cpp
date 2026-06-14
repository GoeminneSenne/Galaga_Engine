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

#include "FormationManager.h"
#include "FormationManagerUpdater.h"
#include "GameStateManager.h"
#include "GameStats.h"
#include "ScoreDisplay.h"
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

	/*
	go = std::make_unique<dae::GameObject>();
	go->GetTransform()->SetLocalPosition(10, 10);
	go->AddComponent<dae::TextureRenderer>();
	go->AddComponent<dae::TextComponent>("0 FPS", font);
	go->AddComponent<dae::FPS>();
	scene.Add(std::move(go));
	/////////////////////////////////////////////
	*/

	/*
	///CONTROLS 1
	////////////////////////////////////////////
	go = std::make_unique<dae::GameObject>();
	go->GetTransform()->SetLocalPosition(10, 100);
	go->AddComponent<dae::TextureRenderer>();
	//font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
	//go->AddComponent<dae::TextComponent>("Use WASD to move Bird, C to inflict damage, Z and X to kill ships", font);
	go->AddComponent<dae::TextComponent>("Press Space to fire bullets, Q/D to move", font);
	scene.Add(std::move(go)); 
	///////////////////////////////////////////
	*/

	///SHIP 1
	/////////////////////////////////////////////////////////
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureRenderer>("Galaga.png");
	go->GetTransform()->SetLocalPosition(500, 400);
	auto pLives = go->AddComponent<dae::Lives>(3);
	go->AddComponent<dae::Score>();
	auto pPlayerShip = go->AddComponent<dae::PlayerShip>(0.f, wWidth);
	go->AddComponent<dae::Collider>(32.f, 32.f);
	auto score = go->AddComponent<dae::Score>();

	auto moc = std::make_unique<dae::MoveObjectCommand>(go.get(), glm::vec3(1, 0, 0), 150.f);
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_D, dae::KeyState::Pressed, std::move(moc));
	moc = std::make_unique<dae::MoveObjectCommand>(go.get(), glm::vec3(-1, 0, 0), 150.f);
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_A, dae::KeyState::Pressed, std::move(moc));
	
	moc = std::make_unique<dae::MoveObjectCommand>(go.get(), glm::vec3(1, 0, 0), 150.f);
	dae::InputManager::GetInstance().AddButtonbind(dae::GamepadButton::DPAD_RIGHT, 0, dae::KeyState::Pressed, std::move(moc));
	moc = std::make_unique<dae::MoveObjectCommand>(go.get(), glm::vec3(-1, 0, 0), 150.f);
	dae::InputManager::GetInstance().AddButtonbind(dae::GamepadButton::DPAD_LEFT, 0, dae::KeyState::Pressed, std::move(moc));

	auto sc = std::make_unique<dae::ShootCommand>(pPlayerShip);
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_SPACE, dae::KeyState::Down, std::move(sc));
	sc = std::make_unique<dae::ShootCommand>(pPlayerShip);
	dae::InputManager::GetInstance().AddButtonbind(dae::GamepadButton::A,0,  dae::KeyState::Down, std::move(sc));

	scene.Add(std::move(go));
	////////////////////////////////////////////////////////////

	///LivesDisplay
	/////////////////////////////////////////////////////////////
	go = std::make_unique<dae::GameObject>();
	auto livesDisplay = go->AddComponent<dae::LivesDisplay>(pLives);
	float livesY = (float)dae::Window::GetInstance().GetHeight() - 42.f;
	go->GetTransform()->SetLocalPosition(10, livesY);
	pLives->GetSubject()->AddObserver(livesDisplay);

	scene.Add(std::move(go));
	/////////////////////////////////////////////////////////////

	///ScoreDisplay
	////////////////////////////////////////////////////////////
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureRenderer>();
	go->AddComponent<dae::TextComponent>("0", font);
	auto scoreDisplay = go->AddComponent<dae::ScoreDisplay>();
	score->GetSubject()->AddObserver(scoreDisplay);
	go->GetTransform()->SetLocalPosition(10, 0);
	scene.Add(std::move(go));
	////////////////////////////////////////////////////////////

	/// Enemy Ship
	//////////////////////////////////////////////////////////
	FormationManager::GetInstance().Init();

	go = std::make_unique<dae::GameObject>();
	go->AddComponent<FormationManagerUpdater>();

	scene.Add(std::move(go));
	//////////////////////////////////////////////////////////

	//Reset GameStats
	GameStats::GetInstance().ResetStats();

	//Start Sound Effect
	//TODO volume 0.1
	dae::ServiceLocator::GetSoundSystem().PlaySFX("./Data/Start.mp3", 0.f);

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
	go->GetTransform()->SetLocalPosition(50.f, 50.f);
	auto menu = go->AddComponent<MenuComponent>();
	scene.Add(std::move(go));
		
	//Start Level button
	go = std::make_unique<dae::GameObject>();
	dae::GameObject* buttonObj = go.get();
	go->GetTransform()->SetLocalPosition(130.f, 100.f);
	go->AddComponent<dae::TextureRenderer>("Button.png");
	go->AddComponent<UIButton>(menu, "StartLevel");
	scene.Add(std::move(go));


	//Start text
	auto textGo = std::make_unique<dae::GameObject>();
	textGo->SetParent(buttonObj, false);
	textGo->GetTransform()->SetLocalPosition(10.f, 5.f);

	textGo->AddComponent<dae::TextureRenderer>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 17);
	textGo->AddComponent<dae::TextComponent>("Start", font);
	scene.Add(std::move(textGo));
	
}
