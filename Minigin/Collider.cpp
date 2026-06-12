#include "Collider.h"

#include "CollisionManager.h"
#include "GameObject.h"

dae::Collider::Collider(GameObject* pOwner, float width, float height)
	: Component(pOwner), m_width(width), m_height(height)
{
	CollisionManager::GetInstance().AddCollider(this);
}

dae::Collider::~Collider()
{
	CollisionManager::GetInstance().RemoveCollider(this);
}

bool dae::Collider::IsColliding(const Collider& other) const
{
	glm::vec2 thisMin{ GetMin() };
	glm::vec2 thisMax{ GetMax() };
	
	glm::vec2 otherMin{ other.GetMin() };
	glm::vec2 otherMax{ other.GetMax() };

	if (thisMax.x < otherMin.x || thisMin.x > otherMax.x) return false;
	if (thisMax.y < otherMin.y || thisMin.y > otherMax.y) return false;

	return true;
}

glm::vec2 dae::Collider::GetMin() const
{
	glm::vec3 pos = GetOwner()->GetTransform()->GetWorldPosition();
	return glm::vec2{ pos.x, pos.y };
}

glm::vec2 dae::Collider::GetMax() const
{
	glm::vec3 pos = GetOwner()->GetTransform()->GetWorldPosition();
	return glm::vec2{ pos.x + m_width, pos.y + m_height };
}
