#pragma once
#include "EventQueue.h"
#include "../ICommand.h"
#include "../Components/Score.h"

namespace dae
{
	class Score;

	class AddScoreCommand : public ICommand
	{
	public: 
		explicit AddScoreCommand(Score* pScore, GameObject* pTarget, int scoreIncrease) : m_scoreIncrease{ scoreIncrease }, pScore{ pScore }, pTarget{ pTarget } {}

		void Execute(float deltaTime) override;
	private:
		int m_scoreIncrease;
		Score* pScore;
		GameObject* pTarget;
	};
}

inline void dae::AddScoreCommand::Execute(float)
{
	//pScore->AddScore(m_scoreIncrease);
	EventQueue::GetInstance().SendEvent(make_sdbm_hash("ScoreAdded"), std::make_unique<ScoreAddedArgs>(m_scoreIncrease, pTarget));
}
