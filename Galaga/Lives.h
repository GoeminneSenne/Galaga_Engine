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
		void Update(float deltaTime) override;
		void OnCollision(GameObject* other) override;

	private:
		int m_numLives;
		std::unique_ptr<Subject> m_pSubject;

		bool m_isImmortal{false};
		float m_immortalTime{0.f};
		constexpr static float m_maxImmortalTime{ 1.f };

	};
}