#include "PlayerShip.h"

#include <memory>
#include <Event.h>
#include <EventQueue.h>



dae::PlayerShip::PlayerShip(GameObject* pOwner)
	: Component(pOwner)
{
}

void dae::PlayerShip::ShootBullet()
{
	std::unique_ptr<EventArgs> args = std::make_unique<PlaySFXArgs>("./Data/PlayerShoot.mp3");
	EventQueue::GetInstance().SendEvent(make_sdbm_hash("PlaySFX"), std::move(args));
}
