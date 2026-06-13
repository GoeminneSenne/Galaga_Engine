#include "GameStates.h"
#include "Event.h"
#include "EventArgs.h"
#include "EventQueue.h"
#include "SceneCreator.h"

galaga::GameState::GameState() = default;
galaga::GameState::~GameState() = default;

void galaga::GameState::OnEnter(GameStateManager*) {}

void galaga::GameState::OnExit(GameStateManager*) {}

std::unique_ptr<galaga::GameState> galaga::GameState::HandleEvent(GameStateManager*, const dae::Event&)
{
	return nullptr;
}

galaga::MainMenuState::MainMenuState() = default;
galaga::MainMenuState::~MainMenuState() = default;

void galaga::MainMenuState::OnEnter(GameStateManager*)
{
	SceneCreator::GetInstance().CreateMainMenu();
}

std::unique_ptr<galaga::GameState> galaga::MainMenuState::HandleEvent(GameStateManager*, const dae::Event& event)
{
	if (event.id == dae::make_sdbm_hash("ButtonClicked"))
	{
		ButtonClickedArgs* args = static_cast<ButtonClickedArgs*>(event.args.get());
		if (args->buttonName == "StartLevel")
		{
			return std::make_unique<LevelState>();
		}
	}

	return nullptr;
}

galaga::LevelState::LevelState() = default;
galaga::LevelState::~LevelState() = default;

void galaga::LevelState::OnEnter(GameStateManager*)
{
	SceneCreator::GetInstance().CreateGameScene();
}

std::unique_ptr<galaga::GameState> galaga::LevelState::HandleEvent(GameStateManager*,
	const dae::Event& event)
{
	if (event.id == dae::make_sdbm_hash("GameOver"))
	{
		return std::make_unique<MainMenuState>();
	}

	return nullptr;
}
