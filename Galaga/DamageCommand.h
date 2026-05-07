#pragma once
#include <ICommand.h>
#include "Lives.h"

namespace dae
{
	class DamageCommand : public ICommand
	{
	public:
		explicit DamageCommand(Lives* pLives) : pLives{pLives} {}
		~DamageCommand() override = default;

		void Execute(float deltaTime) override;

	private:
		Lives* pLives;
	};
}
