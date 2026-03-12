#pragma once
#include <memory>
#include <vector>

#include "InputBinding.h"
#include "Singleton.h"
#include "Input/Gamepad.h"
#include "Input/Keyboard.h"

namespace dae
{
	enum class KeyState;
	class Command;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		explicit InputManager();
		~InputManager() override;

		bool ProcessInput();

		void AddKeybind(SDL_Scancode key, KeyState state, std::unique_ptr<Command> pCommand);
		void AddButtonbind(GamepadButton button, int gamepadIndex, KeyState state, std::unique_ptr<Command> pCommand);

		void RemoveKeybind(SDL_Scancode key, KeyState state);
		void RemoveButtonbind(GamepadButton button, int gamepadIndex, KeyState state);
	private:
		std::vector<Keybind> m_keybinds;
		std::vector<ButtonBind> m_buttonbinds;

		Keyboard m_keyboard;

		int m_nrOfGamepads{ 4 }; //Max for Xinput
		std::vector<std::unique_ptr<Gamepad>> m_gamepads;

	};

}
