#include "HealthDisplay.h"

#include "GameObject.h"
#include "Health.h"
#include "TextComponent.h"

dae::HealthDisplay::HealthDisplay(GameObject* pOwner, Health* pHealth)
	: Component{pOwner}
{
	m_pTextComponent = pOwner->GetComponent<TextComponent>();

	if (pHealth)
	{
		UpdateText(pHealth->GetNumLives());
	}
}


void dae::HealthDisplay::Notify(EventType eventType, GameObject* object)
{
	if (eventType == EventType::PlayerDied)
	{
		if (auto health = object->GetComponent<Health>())
		{
			UpdateText(health->GetNumLives());
		}
	}
}

void dae::HealthDisplay::UpdateText(int health) const
{
	if (m_pTextComponent)
	{
		m_pTextComponent->SetText("# lives: " + std::to_string(health));
	}
}

