#pragma once

#include "Component.h"

namespace dae
{
	class Health : public Component
	{
	public:
		explicit Health(GameObject* pOwner, int numLives);
		~Health() override = default;

		void Damage();

	private:
		int m_numLives;
	};
}