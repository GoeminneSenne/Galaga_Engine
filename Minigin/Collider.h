#pragma once

#include <glm/glm.hpp>

#include "Component.h"

namespace dae
{
	class Collider final : public Component
	{
	public:
		explicit Collider(GameObject* pOwner, float width, float height);
		~Collider() override;
		Collider(const Collider&) = delete;
		Collider(Collider&&) = delete;
		Collider& operator=(const Collider&) = delete;
		Collider& operator=(Collider&&) = delete;

		bool IsColliding(const Collider& other) const;
		glm::vec2 GetMin() const;
		glm::vec2 GetMax() const;

	private:
		float m_width{};
		float m_height{};
	};
}