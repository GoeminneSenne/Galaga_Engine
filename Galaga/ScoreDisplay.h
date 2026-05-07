#pragma once
#include <Component.h>
#include <IObserver.h>

namespace dae
{
	class TextComponent;
	class Score;

	class ScoreDisplay : public Component, public IObserver
	{
	public:
		explicit ScoreDisplay(GameObject* pOwner);
		~ScoreDisplay() override = default;

		void Notify(EventId eventId, GameObject* object) override;

	private:
		void UpdateText(int score) const;

		TextComponent* m_pTextComponent;
	};
}