#pragma once
#include "../Command.h"
#include "../Components/Health.h"

namespace dae
{
	class DamageCommand : public Command
	{
	public:
		explicit DamageCommand(Health* pHealth) : pHealth{pHealth} {}
		~DamageCommand() override = default;

		void Execute(float deltaTime) override;

	private:
		Health* pHealth;
	};
}
