#pragma once
#include "Component.h"
#include "FormationManager.h"

namespace galaga
{
	class FormationManagerUpdater final : public dae::Component
	{
	public:
		explicit FormationManagerUpdater(dae::GameObject* pOwner);
		~FormationManagerUpdater() override = default;

		void Update(float deltaTime) override;

	private:
		FormationManager* m_pFormationManager;
	};
}
