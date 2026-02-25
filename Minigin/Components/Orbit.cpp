#include "Orbit.h"

#include "GameObject.h"
#include "Transform.h"

dae::Orbit::Orbit(GameObject* pOwner, const glm::vec3& center, float radius, float rotationSpeed)
	: Component{pOwner}
	, m_center{center}
	, m_radius{radius}
	, m_rotationSpeed{rotationSpeed}
{
	m_pTransform = pOwner->GetTransform();
}

void dae::Orbit::Update(float deltaTime)
{
	m_currentAngle += m_rotationSpeed * deltaTime;

	glm::vec3 circlePos{ glm::cos(m_currentAngle), glm::sin(m_currentAngle), 0.f};
	circlePos *= m_radius;

	m_pTransform->SetLocalPosition(m_center + circlePos);
}