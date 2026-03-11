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

	//Process Input
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


	
	//Copy state to previous 
	m_previousKeyboardState.assign(m_currentKeyboardState, m_currentKeyboardState + m_numKeys);

	return true;
}

void dae::InputManager::AddKeybind(SDL_Scancode key, KeyState state, std::unique_ptr<Command> pCommand)
{
	m_keybinds.emplace_back(key, state, std::move(pCommand));
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
