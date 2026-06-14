#include "MenuComponent.h"

#include <algorithm>
#include <memory>

#include "InputManager.h"
#include "MenuCommands.h"

galaga::MenuComponent::MenuComponent(dae::GameObject* pOwner)
	: Component(pOwner)
{
	auto nextCmd = std::make_unique<NextButtonCommand>(this);
	auto prevCmd = std::make_unique<PreviousButtonCommand>(this);
	auto clickCmd = std::make_unique<ClickButtonCommand>(this);

	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_RIGHT, dae::KeyState::Down, std::move(nextCmd));
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_LEFT, dae::KeyState::Down, std::move(prevCmd));
	dae::InputManager::GetInstance().AddKeybind(SDL_SCANCODE_SPACE, dae::KeyState::Down, std::move(clickCmd));

	nextCmd = std::make_unique<NextButtonCommand>(this);
	prevCmd = std::make_unique<PreviousButtonCommand>(this);
	clickCmd = std::make_unique<ClickButtonCommand>(this);

	dae::InputManager::GetInstance().AddButtonbind(dae::GamepadButton::DPAD_RIGHT, 0, dae::KeyState::Down, std::move(nextCmd));
	dae::InputManager::GetInstance().AddButtonbind(dae::GamepadButton::DPAD_LEFT, 0, dae::KeyState::Down, std::move(prevCmd));
	dae::InputManager::GetInstance().AddButtonbind(dae::GamepadButton::A, 0, dae::KeyState::Down, std::move(clickCmd));
}

galaga::MenuComponent::~MenuComponent()
{
	//Incase Menu gets destroyed before buttons unregistered
	for (const auto& button : m_buttons)
	{
		button->DetachMenu();
	}

	dae::InputManager::GetInstance().RemoveKeybind(SDL_SCANCODE_RIGHT, dae::KeyState::Down);
	dae::InputManager::GetInstance().RemoveKeybind(SDL_SCANCODE_LEFT, dae::KeyState::Down);
	dae::InputManager::GetInstance().RemoveKeybind(SDL_SCANCODE_SPACE, dae::KeyState::Down);

	dae::InputManager::GetInstance().RemoveButtonbind(dae::GamepadButton::DPAD_RIGHT, 0, dae::KeyState::Down);
	dae::InputManager::GetInstance().RemoveButtonbind(dae::GamepadButton::DPAD_LEFT, 0, dae::KeyState::Down);
	dae::InputManager::GetInstance().RemoveButtonbind(dae::GamepadButton::A, 0, dae::KeyState::Down);
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

void galaga::MenuComponent::ClickSelectedButton()
{
	m_buttons[m_selectedButton]->OnClick();
}
