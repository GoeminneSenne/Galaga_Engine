#pragma once
#include "IObserver.h"
#include "Component.h"
#include "SteamAchievements.h"
#include "Components/Score.h"

namespace dae
{
	class AchievementObserver : public Component, public IObserver
	{
	public:
		explicit AchievementObserver(GameObject* pOwner) : Component{ pOwner } {}

		void Notify(EventId eventId, GameObject* object) override;
	};
}


inline void dae::AchievementObserver::Notify(EventId eventId, GameObject* object)
{
	if (eventId == make_sdbm_hash("ScoreAdded"))
	{
		auto score = object->GetComponent<Score>();

		if (score)
		{
			if (score->GetScore() >= 500)
			{
				CSteamAchievements::GetInstance().SetAchievement("ACH_WIN_ONE_GAME");
			}
		}
	}
}
