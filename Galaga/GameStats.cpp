#include "GameStats.h"

#include "EventQueue.h"

void galaga::GameStats::ResetStats()
{
	dae::EventQueue::GetInstance().Subscribe(this);
}

void galaga::GameStats::HandleEvent(const dae::Event& event)
{
	if (event.id == dae::make_sdbm_hash("ShootBullet"))
	{
		++m_shotsFired;
	}
}
