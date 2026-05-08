#include "ShootCommand.h"

#include "PlayerShip.h"

dae::ShootCommand::ShootCommand(PlayerShip* pPlayer)
	: m_pPlayer(pPlayer)
{
}

void dae::ShootCommand::Execute(float)
{
	if (m_pPlayer && m_pPlayer->CanShoot())
	{
		m_pPlayer->ShootBullet();
	}
}
