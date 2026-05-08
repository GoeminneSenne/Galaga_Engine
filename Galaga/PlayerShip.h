#pragma once

#include <Component.h>

#include "IEventListener.h"
#include "SDL3/SDL_rect.h"

namespace dae
{
	class PlayerShip : public Component, IEventListener
	{
	public:
		explicit PlayerShip(GameObject* pOwner);
		~PlayerShip() override;

		void Update(float deltaTime) override;
		void HandleEvent(const Event& event) override;

		void ShootBullet();
		bool CanShoot() const;

	private:
		int m_activeBullets{};
		float m_currentCooldown{};

		constexpr static SDL_FRect m_srcRect{ 109.f, 1.f, 16.f, 16.f };
		constexpr static float m_width{ 32.f };
		constexpr static float m_height{ 32.f };
		constexpr static int m_maxActiveBullets{ 2 };
		constexpr static float m_shootCooldown{ .18f };
	};
}
