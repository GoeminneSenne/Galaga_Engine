#pragma once
#include <memory>
#include <vector>

#include "InputBinding.h"
#include "Singleton.h"


#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <Xinput.h>
#endif


namespace dae
{
	enum class KeyState;
	class Command;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		void AddKeybind(SDL_Scancode key, KeyState state, std::unique_ptr<Command> pCommand);
		void AddButtonbind(GamepadButton button, KeyState state, std::unique_ptr<Command> pCommand);
	private:

		bool IsKeyDown(SDL_Scancode key) const;
		bool IsKeyUp(SDL_Scancode key) const;
		bool IsKeyPressed(SDL_Scancode key) const;

		std::vector<Keybind> m_keybinds;

		const bool* m_currentKeyboardState{};
		std::vector<bool> m_previousKeyboardState;
		int m_numKeys{};


		bool IsButtonDown(GamepadButton button) const;
		bool IsButtonUp(GamepadButton button) const;
		bool IsButtonPressed(GamepadButton button) const;

		WORD GamepadButtonToXinput(GamepadButton button) const;

		XINPUT_STATE previousState{};
		XINPUT_STATE currentState{};

		WORD buttonsPressedThisFrame{};
		WORD buttonsReleasedThisFrame{};

		std::vector<ButtonBind> m_buttonbinds;
	};

}
