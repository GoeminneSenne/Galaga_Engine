#include "Bullet.h"

#include "GameObject.h"
#include "TextureRenderer.h"

dae::Bullet::Bullet(GameObject* pOwner, const glm::vec3& position)
	: Component(pOwner)
{
	GetOwner()->GetTransform()->SetLocalPosition(position);

	auto texture = GetOwner()->GetComponent<TextureRenderer>();
	texture->SetSourceRect(m_srcRect);
	texture->SetDestinationSize(m_width, m_height);
}
