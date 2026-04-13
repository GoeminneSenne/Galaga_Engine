#pragma once
#include "../ICommand.h"
#include "../Components/Score.h"

namespace dae
{
	class Score;

	class AddScoreCommand : public ICommand
	{
	public: 
		explicit AddScoreCommand(Score* pScore, int scoreIncrease) : m_scoreIncrease{ scoreIncrease }, pScore{ pScore } {}

		void Execute(float deltaTime) override;
	private:
		int m_scoreIncrease;
		Score* pScore;
	};
}

inline void dae::AddScoreCommand::Execute(float)
{
	pScore->AddScore(m_scoreIncrease);
}
