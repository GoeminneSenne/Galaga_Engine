#include "ScoreDisplay.h"

#include "GameObject.h"
#include "Score.h"
#include "TextComponent.h"

dae::ScoreDisplay::ScoreDisplay(GameObject* pOwner)
	:Component{pOwner}
{
	m_pTextComponent = pOwner->GetComponent<TextComponent>();
}

void dae::ScoreDisplay::Notify(EventType eventType, GameObject* object)
{
	if (eventType == EventType::ScoreAdded)
	{
		if (auto score = object->GetComponent<Score>())
		{
			UpdateText(score->GetScore());
		}
	}
}

void dae::ScoreDisplay::UpdateText(int score) const
{
	if (m_pTextComponent)
	{
		m_pTextComponent->SetText("Score: " + std::to_string(score));
	}
}
