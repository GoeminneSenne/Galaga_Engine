#pragma once
#include <ICommand.h>

#include "MenuComponent.h"

namespace galaga
{
	class NextButtonCommand final : public dae::ICommand
	{
	public:
		explicit NextButtonCommand(MenuComponent* pMenu) : m_pMenu(pMenu) {}
		~NextButtonCommand() override = default;

		void Execute(float deltaTime) override
		{
			if (!m_pMenu) return;
			m_pMenu->SelectNextButton();
		}

	private:
		MenuComponent* m_pMenu{};
	};

	class PreviousButtonCommand final : public dae::ICommand
	{
	public:
		explicit PreviousButtonCommand(MenuComponent* pMenu) : m_pMenu(pMenu) {}
		~PreviousButtonCommand()() override = default;

		void Execute(float deltaTime) override
		{
			if (!m_pMenu) return;
			m_pMenu->SelectPreviousButton();
		}

	private:
		MenuComponent* m_pMenu{};
	};
}
