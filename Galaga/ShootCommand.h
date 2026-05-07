#pragma once
#include <ICommand.h>

namespace dae
{
	class PlayerShip;

	class ShootCommand : public ICommand
	{
	public:
		explicit ShootCommand(PlayerShip* pPlayer);
		~ShootCommand() override = default;
		
		void Execute(float deltaTime) override;

	private:
		PlayerShip* m_pPlayer{};
	};
}
