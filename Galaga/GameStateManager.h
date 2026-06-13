#pragma once
#include "Singleton.h"
#include <memory>

#include "GameStates.h"
#include "IEventListener.h"

namespace galaga
{
	class GameStateManager final : public dae::Singleton<GameStateManager>, public dae::IEventListener
	{
	public:
		void Init();

		void HandleEvent(const dae::Event& event) override;

	private:
		std::unique_ptr<GameState> m_currentState{};
	};
}
