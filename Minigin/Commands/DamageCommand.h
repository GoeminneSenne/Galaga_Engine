#pragma once
#include "../ICommand.h"
#include "../Components/Health.h"

namespace dae
{
	class DamageCommand : public ICommand
	{
	public:
		explicit DamageCommand(Health* pHealth) : pHealth{pHealth} {}
		~DamageCommand() override = default;

		void Execute(float deltaTime) override;

	private:
		Health* pHealth;
	};
}
