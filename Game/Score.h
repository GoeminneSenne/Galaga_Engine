#pragma once
#include <memory>

#include "IEventListener.h"
#include <Component.h>
#include <Subject.h>

namespace dae
{
	class Score : public Component, IEventListener
	{
	public:
		explicit Score(GameObject* pOwner);

		Subject* GetSubject() const;
		int GetScore() const;

		void HandleEvent(const Event& event) override;

		void AddScore(int score);

	private:
		int m_score;
		std::unique_ptr<Subject> m_pSubject;
	};
}