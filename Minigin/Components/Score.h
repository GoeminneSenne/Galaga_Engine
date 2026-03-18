#pragma once
#include <memory>

#include "../Component.h"
#include "../Subject.h"

namespace dae
{
	class Score : public Component
	{
	public:
		explicit Score(GameObject* pOwner);

		Subject* GetSubject() const;
		int GetScore() const;

		void AddScore(int score);

	private:
		int m_score;
		std::unique_ptr<Subject> m_pSubject;
	};
}