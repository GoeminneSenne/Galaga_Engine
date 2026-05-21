#include "Keyboard.h"

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_keyboard.h"

dae::Keyboard::Keyboard()
{
	m_currentState = SDL_GetKeyboardState(&m_numKeys);
}

void dae::Keyboard::UpdateState()
{

	SDL_PumpEvents();
	m_currentState = SDL_GetKeyboardState(&m_numKeys);
}

void dae::Keyboard::UpdatePreviousState()
{
	m_previousState.assign(m_currentState, m_currentState + m_numKeys);
}

bool dae::Keyboard::IsKeyDown(SDL_Scancode key) const
{

	return m_currentState[key] && !m_previousState[key];
}

bool dae::Keyboard::IsKeyUp(SDL_Scancode key) const
{
	return !m_currentState[key] && m_previousState[key];
}

bool dae::Keyboard::IsKeyPressed(SDL_Scancode key) const
{
	return m_currentState[key];
}
