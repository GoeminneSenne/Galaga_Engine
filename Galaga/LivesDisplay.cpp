#include "LivesDisplay.h"

#include "GameObject.h"
#include "Lives.h"
#include "TextComponent.h"

dae::LivesDisplay::LivesDisplay(GameObject* pOwner, Lives* pLives)
	: Component{pOwner}
{
	m_pTextComponent = pOwner->GetComponent<TextComponent>();

	if (pLives)
	{
		UpdateText(pLives->GetNumLives());
	}
}


void dae::LivesDisplay::Notify(EventId eventId, GameObject* object)
{
	if (eventId == make_sdbm_hash("PlayerDied"))
	{
		if (auto livesComp = object->GetComponent<Lives>())
		{
			UpdateText(livesComp->GetNumLives());
		}
	}
}

void dae::LivesDisplay::UpdateText(int numLives) const
{
	if (m_pTextComponent)
	{
		m_pTextComponent->SetText("# lives: " + std::to_string(numLives));
	}
}

