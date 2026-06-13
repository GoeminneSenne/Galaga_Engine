#pragma once
#include <memory>

namespace dae
{
	struct Event;
}

namespace galaga
{
	class GameStateManager;

	class GameState
	{
	public:
		explicit GameState();
		virtual ~GameState();

		virtual void OnEnter(GameStateManager* pGameStateManager);
		virtual void OnExit(GameStateManager* pGameStateManager);

		virtual std::unique_ptr<GameState> HandleEvent(GameStateManager* pGameStateManager, const dae::Event& event);
	};

	class MainMenuState final : public GameState
	{
	public:
		explicit MainMenuState();
		~MainMenuState() override;

		void OnEnter(GameStateManager* pGameStateManager) override;
		std::unique_ptr<GameState> HandleEvent(GameStateManager* pGameStateManager, const dae::Event& event) override;
	};

	class LevelState final : public GameState
	{
	public:
		explicit LevelState();
		~LevelState() override;

		void OnEnter(GameStateManager* pGameStateManager) override;
		std::unique_ptr<GameState> HandleEvent(GameStateManager* pGameStateManager, const dae::Event& event) override;
	};
}
