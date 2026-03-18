#pragma once
#include "../Component.h"
#include "../Observer.h"

namespace dae
{
	class TextComponent;
	class Score;

	class ScoreDisplay : public Component, public Observer
	{
	public:
		explicit ScoreDisplay(GameObject* pOwner);
		~ScoreDisplay() override = default;

		void Notify(EventType eventType, GameObject* object) override;

	private:
		void UpdateText(int score) const;

		TextComponent* m_pTextComponent;
	};
}