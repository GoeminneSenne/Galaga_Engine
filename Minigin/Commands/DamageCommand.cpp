#include "DamageCommand.h"

void dae::DamageCommand::Execute(float)
{
	if (pHealth) pHealth->Damage();
}
