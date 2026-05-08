#pragma once
#include <Component.h>

#include "Event.h"
#include "glm/vec3.hpp"
#include "SDL3/SDL_rect.h"

namespace dae
{
	class Bullet : public Component
	{
	public:
		explicit Bullet(GameObject* pOwner, const glm::vec3& position);
		~Bullet() override = default;

		void Update(float deltaTime) override;

	private:
		float m_currentLifetime{};

		constexpr static float m_maxLifetime{ 1.f };
		constexpr static float m_speed{100.f};
		constexpr static SDL_FRect m_srcRect{ 307.f, 154.f, 16.f, 16.f };
		constexpr static float m_width{ 32.f };
		constexpr static float m_height{ 32.f };

	};

	struct BulletDestroyedArgs : public EventArgs
	{
		bool hasHitEnemy;
		//TODO: Original ship as member for multiplayer
	};
}
