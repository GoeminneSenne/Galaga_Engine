#pragma once
#include "EventQueue.h"
#include <ICommand.h>
#include "Score.h"

namespace dae
{
	class Score;

	class AddScoreCommand : public ICommand
	{
	public: 
		explicit AddScoreCommand(int scoreIncrease, GameObject* pTarget) : m_scoreIncrease{ scoreIncrease }, pTarget{ pTarget } {}

		void Execute(float deltaTime) override;
	private:
		int m_scoreIncrease;
		GameObject* pTarget;
	};
}

inline void dae::AddScoreCommand::Execute(float)
{
	//pScore->AddScore(m_scoreIncrease);
	EventQueue::GetInstance().SendEvent(make_sdbm_hash("ScoreAdded"), std::make_unique<ScoreAddedArgs>(m_scoreIncrease, pTarget));
}
