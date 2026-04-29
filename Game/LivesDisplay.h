#pragma once
#include <Component.h>
#include <IObserver.h>

namespace dae
{
	class TextComponent;
	class Lives;

	class LivesDisplay : public Component, public IObserver
	{
	public:
		explicit LivesDisplay(GameObject* pOwner, Lives* pLives = nullptr);

		void Notify(EventId eventId, GameObject* object) override;

	private:
		void UpdateText(int numLives) const;

		TextComponent* m_pTextComponent;
	};
}