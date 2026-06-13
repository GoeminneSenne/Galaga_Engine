#include "MenuComponent.h"

galaga::MenuComponent::MenuComponent(dae::GameObject* pOwner)
	: Component(pOwner)
{}

galaga::MenuComponent::~MenuComponent()
{
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
