#include "Score.h"

dae::Score::Score(GameObject* pOwner)
	:Component{pOwner}, m_score{0}, m_pSubject{std::make_unique<Subject>()}
{}

dae::Subject* dae::Score::GetSubject() const
{
	return m_pSubject.get();
}

int dae::Score::GetScore() const
{
	return m_score;
}

void dae::Score::AddScore(int score)
{
	m_score += score;
	m_pSubject->NotifyObservers(make_sdbm_hash("ScoreAdded"), GetOwner());
}
