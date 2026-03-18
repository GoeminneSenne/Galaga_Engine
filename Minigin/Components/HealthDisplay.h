#pragma once
#include "../Component.h"
#include "../Observer.h"

namespace dae
{
	class TextComponent;
	class Health;

	class HealthDisplay : public Component, public Observer
	{
	public:
		explicit HealthDisplay(GameObject* pOwner, Health* pHealth = nullptr);
		~HealthDisplay() override = default;

		void Notify(EventType eventType, GameObject* object) override;

	private:
		void UpdateText(int health) const;

		TextComponent* m_pTextComponent;
	};
}