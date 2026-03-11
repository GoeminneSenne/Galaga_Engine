#pragma once
#include <memory>
#include <vector>

#include "InputBinding.h"
#include "Singleton.h"


namespace dae
{
	enum class KeyState;
	class Command;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		void AddKeybind(SDL_Scancode key, KeyState state, std::unique_ptr<Command> pCommand);
	private:

		bool IsKeyDown(SDL_Scancode key) const;
		bool IsKeyUp(SDL_Scancode key) const;
		bool IsKeyPressed(SDL_Scancode key) const;

		std::vector<Keybind> m_keybinds;

		const bool* m_currentKeyboardState{};
		std::vector<bool> m_previousKeyboardState;
		int m_numKeys{};
	};

}
