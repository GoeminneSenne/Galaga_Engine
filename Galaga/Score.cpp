#include "Score.h"

#include "EventArgs.h"
#include "EventQueue.h"

dae::Score::Score(GameObject* pOwner)
	:Component{pOwner}, m_score{0}, m_pSubject{std::make_unique<Subject>()}
{
	EventQueue::GetInstance().Subscribe(this);
}

dae::Score::~Score()
{
	EventQueue::GetInstance().Unsubscribe(this);
}

dae::Subject* dae::Score::GetSubject() const
{
	return m_pSubject.get();
}

int dae::Score::GetScore() const
{
	return m_score;
}

void dae::Score::HandleEvent(const Event& event)
{
	if (event.id == make_sdbm_hash("ScoreAdded"))
	{
		auto args = dynamic_cast<ScoreAddedArgs*>(event.args.get());
		if (args->pTarget == GetOwner())
		{
			AddScore(args->scoreInc);
		}
	}
	else if (event.id == make_sdbm_hash("EnemyDestroyed"))
	{
		auto args = dynamic_cast<galaga::EnemyDestroyedArgs*>(event.args.get());
		AddScore(args->score);
	}
}

void dae::Score::AddScore(int score)
{
	m_score += score;
	m_pSubject->NotifyObservers(make_sdbm_hash("ScoreAdded"), GetOwner());
}
