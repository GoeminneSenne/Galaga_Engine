#include "Transform.h"

#include "GameObject.h"

void dae::Transform::SetLocalPosition(const float x, const float y, const float z)
{
	m_localPosition.x = x;
	m_localPosition.y = y;
	m_localPosition.z = z;
}

void dae::Transform::SetLocalPosition(const glm::vec3& position) 
{ 
	m_localPosition = position; 
}

const glm::vec3& dae::Transform::GetWorldPosition()
{
	if (m_isPositionDirty)
		UpdateWorldPosition();

	return m_worldPosition;
}

void dae::Transform::UpdateWorldPosition()
{
	if (m_isPositionDirty)
	{
		if (m_pOwner->GetParent() == nullptr)
			m_worldPosition = m_localPosition;
		else
			m_worldPosition = m_pOwner->GetTransform()->GetWorldPosition() + m_localPosition;
	}

	m_isPositionDirty = false;
}

void dae::Transform::SetPositionDirty()
{
	m_isPositionDirty = true;
}

dae::Transform::Transform(GameObject* pOwner)
	: m_pOwner{pOwner} {}
