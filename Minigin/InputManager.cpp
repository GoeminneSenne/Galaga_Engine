#include <SDL3/SDL.h>
#include "InputManager.h"

#include "backends/imgui_impl_sdl3.h"

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT) {
			return false;
		}
		if (e.type == SDL_EVENT_KEY_DOWN) {

		}
		if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
			
		}
		// etc...


		//process event for IMGUI
		ImGui_ImplSDL3_ProcessEvent(&e);
	}

	m_currentKeyboardState = SDL_GetKeyboardState(&m_numKeys);

	//Process Input


	
	//Copy state to previous 
	m_previousKeyboardState.assign(m_currentKeyboardState, m_currentKeyboardState + m_numKeys);

	return true;
}
