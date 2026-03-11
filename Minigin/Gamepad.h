#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <Xinput.h>
#endif
#include <cstdlib>

namespace dae
{
	enum class GamepadButton;
	class Gamepad
	{
	public:
		explicit Gamepad(int gamepadIndex);
	
		void Update();

		bool IsButtonDown(GamepadButton button) const;
		bool IsButtonUp(GamepadButton button) const;
		bool IsButtonPressed(GamepadButton button) const;


	private:
		WORD GamepadButtonToXinput(GamepadButton button) const;

		int m_gamepadIndex;

		XINPUT_STATE m_previousState{};
		XINPUT_STATE m_currentState{};

		WORD m_buttonsPressedThisFrame{};
		WORD m_buttonsReleasedThisFrame{};
	};
}
