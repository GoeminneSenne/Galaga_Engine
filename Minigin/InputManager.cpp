#include <SDL3/SDL.h>
#include "InputManager.h"
#include "InputBinding.h"
#include "Command.h"

#include "backends/imgui_impl_sdl3.h"


bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT) {
			return false;
		}

		// etc...

		

		//process event for IMGUI
		ImGui_ImplSDL3_ProcessEvent(&e);
	}

	m_currentKeyboardState = SDL_GetKeyboardState(&m_numKeys);

	//Process Keyboard Input
	for (const auto& keybind : m_keybinds)
	{
		bool triggered = false;
		switch (keybind.state)
		{
		case KeyState::Down:
			triggered = IsKeyDown(keybind.key);
			break;
		case KeyState::Up:
			triggered = IsKeyUp(keybind.key);
			break;
		case KeyState::Pressed:
			triggered = IsKeyPressed(keybind.key);
			break;
		}

		if (triggered) keybind.pCommand->Execute();
	}

	//Controller input
	CopyMemory(&previousState, &currentState, sizeof(XINPUT_STATE));
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &currentState);

	WORD buttonChanges = currentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
	buttonsPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
	buttonsReleasedThisFrame = buttonChanges & (~currentState.Gamepad.wButtons);

	
	for (const auto& buttonbind : m_buttonbinds)
	{
		bool triggered = false;
		switch (buttonbind.state)
		{
		case KeyState::Down:
			triggered = IsButtonDown(buttonbind.button);
			break;
		case KeyState::Up:
			triggered = IsButtonUp(buttonbind.button);
			break;
		case KeyState::Pressed:
			triggered = IsButtonPressed(buttonbind.button);
			break;
		}

		if (triggered) buttonbind.pCommand->Execute();
	}

	//Copy state to previous 
	m_previousKeyboardState.assign(m_currentKeyboardState, m_currentKeyboardState + m_numKeys);

	return true;
}

void dae::InputManager::AddKeybind(SDL_Scancode key, KeyState state, std::unique_ptr<Command> pCommand)
{
	m_keybinds.emplace_back(key, state, std::move(pCommand));
}

void dae::InputManager::AddButtonbind(unsigned int button, KeyState state, std::unique_ptr<Command> pCommand)
{
	m_buttonbinds.emplace_back(button, state, std::move(pCommand));
}

bool dae::InputManager::IsKeyDown(SDL_Scancode key) const
{
	return m_currentKeyboardState[key] && !m_previousKeyboardState[key];
}

bool dae::InputManager::IsKeyUp(SDL_Scancode key) const
{
	return !m_currentKeyboardState[key] && m_previousKeyboardState[key];
}

bool dae::InputManager::IsKeyPressed(SDL_Scancode key) const
{
	return m_currentKeyboardState[key];
}

bool dae::InputManager::IsButtonDown(unsigned int button) const
{
	return buttonsPressedThisFrame & button;
}

bool dae::InputManager::IsButtonUp(unsigned int button) const
{
	return buttonsReleasedThisFrame & button;
}

bool dae::InputManager::IsButtonPressed(unsigned int button) const
{
	return currentState.Gamepad.wButtons & button;
}
