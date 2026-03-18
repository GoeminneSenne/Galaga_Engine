#pragma once

#include <memory>

#include "Component.h"
#include "Subject.h"

namespace dae
{
	class Health : public Component
	{
	public:
		explicit Health(GameObject* pOwner, int numLives);
		~Health() override = default;

		Subject* GetSubject() const;
		int GetNumLives() const;

		void Damage();

	private:
		int m_numLives;
		std::unique_ptr<Subject> m_pSubject;
	};
}