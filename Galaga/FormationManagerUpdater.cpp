#include "FormationManagerUpdater.h"

galaga::FormationManagerUpdater::FormationManagerUpdater(dae::GameObject* pOwner)
	: Component(pOwner)
{
	m_pFormationManager = &FormationManager::GetInstance();
}

void galaga::FormationManagerUpdater::Update(float deltaTime)
{
	m_pFormationManager->Update(deltaTime);

	
}
