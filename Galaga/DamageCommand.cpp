#include "DamageCommand.h"

#include "EventQueue.h"
#include "ISoundSystem.h"

void dae::DamageCommand::Execute(float)
{
	if (pLives) pLives->Damage();
}
