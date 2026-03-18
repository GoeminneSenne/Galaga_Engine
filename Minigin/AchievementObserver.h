#pragma once
#include "Observer.h"
#include "Component.h"
#include "SteamAchievements.h"
#include "Components/Score.h"

namespace dae
{
	class AchievementObserver : public Component, public Observer
	{
	public:
		explicit AchievementObserver(GameObject* pOwner) : Component{ pOwner } {}

		void Notify(EventType eventType, GameObject* object) override;
	};
}


inline void dae::AchievementObserver::Notify(EventType eventType, GameObject* object)
{
	if (eventType == EventType::ScoreAdded)
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
