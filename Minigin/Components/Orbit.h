#pragma once
#include "Component.h"

#include <glm/glm.hpp>

namespace dae
{
	class Transform;
	class Orbit : public Component
	{
	public:
		explicit Orbit(GameObject* pOwner, const glm::vec3& center, float radius, float rotationSpeed);

		virtual void Update(float deltaTime) override;

	private:
		Transform* m_pTransform{};

		glm::vec3 m_center{};
		float m_radius{};
		float m_rotationSpeed{};
		float m_currentAngle{};


	};
}