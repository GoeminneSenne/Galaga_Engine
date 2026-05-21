#pragma once
#include <vector>

#include <SDL3/SDL_scancode.h>

namespace dae
{
	class Keyboard
	{
	public:
		explicit Keyboard();

		void UpdateState();
		void UpdatePreviousState();

		bool IsKeyDown(SDL_Scancode key) const;
		bool IsKeyUp(SDL_Scancode key) const;
		bool IsKeyPressed(SDL_Scancode key) const;

	private:
		const bool* m_currentState{};
		std::vector<bool> m_previousState{};
		int m_numKeys{};
	};
}
