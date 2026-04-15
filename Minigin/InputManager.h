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
	class ICommand;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		explicit InputManager();
		~InputManager() override;

		bool ProcessInput(float deltaTime);

		void AddKeybind(SDL_Scancode key, KeyState state, std::unique_ptr<ICommand> pCommand);
		void AddButtonbind(GamepadButton button, int gamepadIndex, KeyState state, std::unique_ptr<ICommand> pCommand);

		void RemoveKeybind(SDL_Scancode key, KeyState state);
		void RemoveButtonbind(GamepadButton button, int gamepadIndex, KeyState state);
	private:
		std::vector<Keybind> m_keybinds;
		std::vector<Buttonbind> m_buttonbinds;

		Keyboard m_keyboard;

		int m_nrOfGamepads{ 4 }; //Max for Xinput
		std::vector<std::unique_ptr<Gamepad>> m_gamepads;

	};

}
