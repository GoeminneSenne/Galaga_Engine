#pragma once

#include <Component.h>

namespace dae
{
	class PlayerShip : public Component
	{
	public:
		explicit PlayerShip(GameObject* pOwner);

		void ShootBullet();

	private:

	};
}