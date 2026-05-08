#pragma once

#include <Component.h>

#include "SDL3/SDL_rect.h"

namespace dae
{
	class PlayerShip : public Component
	{
	public:
		explicit PlayerShip(GameObject* pOwner);

		void Update(float deltaTime) override;

		void ShootBullet();
		bool CanShoot() const;

	private:
		int m_activeBullets{};
		float m_currentCooldown{};

		constexpr static SDL_FRect m_srcRect{ 109.f, 1.f, 16.f, 16.f };
		constexpr static float m_width{ 32.f };
		constexpr static float m_height{ 32.f };
		constexpr static int m_maxActiveBullets{ 2 };
		constexpr static float m_shootCooldown{ .12f };
	};
}
