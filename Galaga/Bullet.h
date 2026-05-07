#pragma once
#include <Component.h>

namespace dae
{
	class Bullet : public Component
	{
	public:
		explicit Bullet(GameObject* pOwner);
		~Bullet() override = default;

	private:
		float m_speed{10.f};

	};
}