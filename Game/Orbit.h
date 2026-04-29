#pragma once
#include "Component.h"

#include <glm/glm.hpp>

namespace dae
{
	class Transform;
	class Orbit : public Component
	{
	public:
		explicit Orbit(GameObject* pOwner, float radius, float rotationSpeed);

		virtual void Update(float deltaTime) override;

	private:
		Transform* m_pTransform{};

		float m_radius{};
		float m_rotationSpeed{};
		float m_currentAngle{};


	};
}