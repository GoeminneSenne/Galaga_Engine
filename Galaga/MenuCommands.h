#pragma once
#include <ICommand.h>

#include "MenuComponent.h"

namespace galaga
{
	//TODO: change to make all these 1 command with function as parameter?
	class NextButtonCommand final : public dae::ICommand
	{
	public:
		explicit NextButtonCommand(MenuComponent* pMenu) : m_pMenu(pMenu) {}
		~NextButtonCommand() override = default;

		void Execute(float) override
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
		~PreviousButtonCommand() override = default;

		void Execute(float) override
		{
			if (!m_pMenu) return;
			m_pMenu->SelectPreviousButton();
		}

	private:
		MenuComponent* m_pMenu{};
	};

	class ClickButtonCommand final : public dae::ICommand
	{
	public:
		explicit ClickButtonCommand(MenuComponent* pMenu) : m_pMenu(pMenu) {}
		~ClickButtonCommand() override = default;

		void Execute(float) override
		{
			if (!m_pMenu) return;
			m_pMenu->ClickSelectedButton();
		}
		
	private:
		MenuComponent* m_pMenu{};
	};
}
