#pragma once
#include <memory>
#include <vector>

#include "InputBinding.h"
#include "Singleton.h"

#include "Gamepad.h"

namespace dae
{
	enum class KeyState;
	class Command;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		explicit InputManager();
		bool ProcessInput();

		void AddKeybind(SDL_Scancode key, KeyState state, std::unique_ptr<Command> pCommand);
		void AddButtonbind(GamepadButton button, int gamepadIndex, KeyState state, std::unique_ptr<Command> pCommand);

		void RemoveKeybind(SDL_Scancode key, KeyState state);
	private:

		bool IsKeyDown(SDL_Scancode key) const;
		bool IsKeyUp(SDL_Scancode key) const;
		bool IsKeyPressed(SDL_Scancode key) const;

		std::vector<Keybind> m_keybinds;

		const bool* m_currentKeyboardState{};
		std::vector<bool> m_previousKeyboardState;
		int m_numKeys{};

		int m_nrOfGamepads{ 4 }; //Max for Xinput
		std::vector<Gamepad> m_gamepads;

		std::vector<ButtonBind> m_buttonbinds;
	};

}
