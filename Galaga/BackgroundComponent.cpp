#include "BackgroundComponent.h"

#include "GameObject.h"

galaga::BackgroundComponent::BackgroundComponent(dae::GameObject* pOwner, float scrollSpeed, float height)
	:Component(pOwner), m_scrollSpeed(scrollSpeed), m_height(height)
{}

void galaga::BackgroundComponent::Update(float deltaTime)
{
	glm::vec3 pos = GetOwner()->GetTransform()->GetLocalPosition();
	pos.y += m_scrollSpeed * deltaTime;

	if (pos.y >= m_height)
	{
		pos.y -= m_height * 2;
	}

	GetOwner()->GetTransform()->SetLocalPosition(pos);
}
