#include "Transform.h"

#include "GameObject.h"

const glm::vec3& dae::Transform::GetLocalPosition() const
{
	return m_localPosition;
}

void dae::Transform::SetLocalPosition(const float x, const float y, const float z)
{
	SetLocalPosition(glm::vec3{ x,y,z });
}

void dae::Transform::SetLocalPosition(const glm::vec3& position) 
{ 
	m_localPosition = position; 
	SetPositionDirty();
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
			m_worldPosition = m_pOwner->GetParent()->GetTransform()->GetWorldPosition() + m_localPosition;
	}

	m_isPositionDirty = false;
}

void dae::Transform::SetPositionDirty()
{
	m_isPositionDirty = true;

	for (auto child : m_pOwner->GetChildren())
	{
		child->GetTransform()->SetPositionDirty();
	}
}

dae::Transform::Transform(GameObject* pOwner)
	: m_pOwner{pOwner} {}
