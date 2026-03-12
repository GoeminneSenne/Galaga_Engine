#include <SDL3/SDL.h>
#include "InputManager.h"
#include "InputBinding.h"
#include "Command.h"
#include "Input/Gamepad.h"

#include "backends/imgui_impl_sdl3.h"

#ifdef _WIN32
#include "Input/XInputGamepad.h"
#else
#include "SDLGamepad.h"
#endif

dae::InputManager::InputManager()
{
	SDL_InitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_GAMEPAD);

	for (int idx{}; idx < m_nrOfGamepads; ++idx)
	{
#ifdef _WIN32
		m_gamepads.push_back(std::make_unique<XInputGamepad>(idx));
#else
		m_gamepads.push_back(std::make_unique<SDLGamepad>(idx));
#endif
	}

	//Check first state of SDL keyboard
	m_currentKeyboardState = SDL_GetKeyboardState(&m_numKeys);

}

dae::InputManager::~InputManager()
{
	SDL_QuitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_GAMEPAD);
}

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

	m_previousKeyboardState.assign(m_currentKeyboardState, m_currentKeyboardState + m_numKeys);
	m_currentKeyboardState = SDL_GetKeyboardState(&m_numKeys);

	//Process Keyboard Input
	for (const auto& [key, state, pCommand] : m_keybinds)
	{
		bool triggered = false;
		switch (state)
		{
		case KeyState::Down:
			triggered = IsKeyDown(key);
			break;
		case KeyState::Up:
			triggered = IsKeyUp(key);
			break;
		case KeyState::Pressed:
			triggered = IsKeyPressed(key);
			break;
		}

		if (triggered) pCommand->Execute();
	}

	//Controller input
	for (auto& gamepad : m_gamepads)
	{
		gamepad->Update();
	}
	
	for (const auto& buttonbind : m_buttonbinds)
	{
		bool triggered = false;
		switch (buttonbind.state)
		{
		case KeyState::Down:
			triggered = m_gamepads[buttonbind.gamepadIndex]->IsButtonDown(buttonbind.button);
			break;
		case KeyState::Up:
			triggered = m_gamepads[buttonbind.gamepadIndex]->IsButtonUp(buttonbind.button);
			break;
		case KeyState::Pressed:
			triggered = m_gamepads[buttonbind.gamepadIndex]->IsButtonPressed(buttonbind.button);
			break;
		}

		if (triggered) buttonbind.pCommand->Execute();
	}

	//Copy state to previous 

	return true;
}

void dae::InputManager::AddKeybind(SDL_Scancode key, KeyState state, std::unique_ptr<Command> pCommand)
{
	m_keybinds.emplace_back(key, state, std::move(pCommand));
}

void dae::InputManager::AddButtonbind(GamepadButton button, int gamepadIndex, KeyState state, std::unique_ptr<Command> pCommand)
{
	m_buttonbinds.emplace_back(button, gamepadIndex, state, std::move(pCommand));
}

void dae::InputManager::RemoveKeybind(SDL_Scancode key, KeyState state)
{
	std::erase_if(m_keybinds, [key, state](const Keybind& bind) {return bind.key == key && bind.state == state; });
}

void dae::InputManager::RemoveButtonbind(GamepadButton button, int gamepadIndex, KeyState state)
{
	std::erase_if(m_buttonbinds, [button, gamepadIndex, state](const ButtonBind& bind)
		{return bind.button == button && bind.gamepadIndex == gamepadIndex && bind.state == state; }
	);
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

