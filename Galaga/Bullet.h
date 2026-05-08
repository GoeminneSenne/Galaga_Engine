#pragma once
#include <Component.h>

#include "glm/vec3.hpp"
#include "SDL3/SDL_rect.h"

namespace dae
{
	class Bullet : public Component
	{
	public:
		explicit Bullet(GameObject* pOwner, const glm::vec3& position);
		~Bullet() override = default;

	private:
		//float m_speed{10.f};
		constexpr static SDL_FRect m_srcRect{ 307.f, 154.f, 16.f, 16.f };
		constexpr static float m_width{ 32.f };
		constexpr static float m_height{ 32.f };

	};
}
