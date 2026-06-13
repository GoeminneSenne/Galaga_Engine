#include "MenuComponent.h"

#include <algorithm>

galaga::MenuComponent::MenuComponent(dae::GameObject* pOwner)
	: Component(pOwner)
{}

galaga::MenuComponent::~MenuComponent()
{
	//Incase Menu gets destroyed before buttons unregistered
	for (const auto& button : m_buttons)
	{
		button->DetachMenu();
	}
}

void galaga::MenuComponent::RegisterButton(UIButton* button)
{
	if (std::ranges::find(m_buttons, button) != m_buttons.end()) return;

	m_buttons.push_back(button);
	
	//Select the first added button by default
	if (m_buttons.size() == 1)
	{
		m_selectedButton = 0;
		button->SetIsSelected(true);
	}
}

void galaga::MenuComponent::UnregisterButton(UIButton* button)
{
	auto itr = std::ranges::find(m_buttons, button);
	if (itr == m_buttons.end()) return;
	m_buttons.erase(itr);
}

void galaga::MenuComponent::SelectNextButton()
{
	m_buttons[m_selectedButton]->SetIsSelected(false);

	++m_selectedButton;
	m_selectedButton = std::min(m_selectedButton, int(m_buttons.size() - 1));

	m_buttons[m_selectedButton]->SetIsSelected(true);
}

void galaga::MenuComponent::SelectPreviousButton()
{
	m_buttons[m_selectedButton]->SetIsSelected(false);

	--m_selectedButton;
	m_selectedButton = std::max(m_selectedButton, 0);

	m_buttons[m_selectedButton]->SetIsSelected(true);
}
