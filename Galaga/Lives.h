#pragma once

#include <memory>

#include "Component.h"
#include "Subject.h"

namespace dae
{
	class Lives : public Component
	{
	public:
		explicit Lives(GameObject* pOwner, int numLives);

		Subject* GetSubject() const;
		int GetNumLives() const;

		void Damage();

	private:
		int m_numLives;
		std::unique_ptr<Subject> m_pSubject;
	};
}