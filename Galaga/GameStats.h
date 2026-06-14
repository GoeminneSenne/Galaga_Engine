#pragma once
#include "IEventListener.h"
#include "Singleton.h"

namespace galaga
{
	class GameStats final : public dae::Singleton<GameStats>, public dae::IEventListener
	{
	public:
		void ResetStats();
		void HandleEvent(const dae::Event& event) override;

	private:
		int m_shotsFired{};
	};
}
