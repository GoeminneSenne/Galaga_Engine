#include "DamageCommand.h"

#include "EventQueue.h"
#include "ISoundSystem.h"

void dae::DamageCommand::Execute(float)
{
	if (pLives) pLives->Damage();

	std::unique_ptr<EventArgs> args = std::make_unique<PlaySFXArgs>("./Data/PlayerShoot.mp3");
	EventQueue::GetInstance().SendEvent(make_sdbm_hash("PlaySFX"),std::move(args));
}
