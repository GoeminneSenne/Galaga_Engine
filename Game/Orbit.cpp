#include "Orbit.h"

#include "GameObject.h"
#include "Transform.h"
#include <glm/ext/scalar_constants.hpp>

dae::Orbit::Orbit(GameObject* pOwner, float radius, float rotationSpeed)
	: Component{pOwner}
	, m_radius{radius}
	, m_rotationSpeed{rotationSpeed}
{
	m_pTransform = pOwner->GetTransform();
}

void dae::Orbit::Update(float deltaTime)
{
	constexpr static float clamp = 2.f * glm::pi<float>();
	
	m_currentAngle += m_rotationSpeed * deltaTime;
	if (m_currentAngle > clamp)
	{
		m_currentAngle -= clamp;
	}
	else if (m_currentAngle < -clamp)
	{
		m_currentAngle += clamp;
	}

	glm::vec3 circlePos{ glm::cos(m_currentAngle), glm::sin(m_currentAngle), 0.f};
	circlePos *= m_radius;

	m_pTransform->SetLocalPosition(circlePos);
}