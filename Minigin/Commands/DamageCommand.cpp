#include "DamageCommand.h"

void dae::DamageCommand::Execute(float)
{
	if (pLives) pLives->Damage();
}
