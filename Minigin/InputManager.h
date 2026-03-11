#pragma once
#include <vector>

#include "Singleton.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

	private:

		bool IsKeyDown(SDL_Scancode key) const;
		bool IsKeyUp(SDL_Scancode key) const;
		bool IsKeyPressed(SDL_Scancode key) const;

		const bool* m_currentKeyboardState{};
		std::vector<bool> m_previousKeyboardState;
		int m_numKeys{};
	};

}
