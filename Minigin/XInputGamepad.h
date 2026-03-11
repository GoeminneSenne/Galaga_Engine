#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <Xinput.h>
#endif
#include "Gamepad.h"

namespace dae
{
	enum class GamepadButton;
	class XInputGamepad : public Gamepad
	{
	public:
		explicit XInputGamepad(int gamepadIndex);

		void Update() override;

		bool IsButtonDown(GamepadButton button) const override;
		bool IsButtonUp(GamepadButton button) const override;
		bool IsButtonPressed(GamepadButton button) const override;


	private:
		static WORD GamepadButtonToXinput(GamepadButton button);

		XINPUT_STATE m_previousState{};
		XINPUT_STATE m_currentState{};

		WORD m_buttonsPressedThisFrame{};
		WORD m_buttonsReleasedThisFrame{};
	};
}
