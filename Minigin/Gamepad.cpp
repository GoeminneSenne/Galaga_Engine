#include "Gamepad.h"
#include "InputBinding.h"

dae::Gamepad::Gamepad(int gamepadIndex)
	:m_gamepadIndex{gamepadIndex}
{}

void dae::Gamepad::Update()
{
	CopyMemory(&m_previousState, &m_currentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_currentState, sizeof(XINPUT_STATE));
	XInputGetState(m_gamepadIndex, &m_currentState);

	WORD buttonChanges = m_currentState.Gamepad.wButtons ^ m_previousState.Gamepad.wButtons;
	m_buttonsPressedThisFrame = buttonChanges & m_currentState.Gamepad.wButtons;
	m_buttonsReleasedThisFrame = buttonChanges & (~m_currentState.Gamepad.wButtons);
}

bool dae::Gamepad::IsButtonDown(GamepadButton button) const
{
	return m_buttonsPressedThisFrame & GamepadButtonToXinput(button);
}

bool dae::Gamepad::IsButtonUp(GamepadButton button) const
{
	return m_buttonsReleasedThisFrame & GamepadButtonToXinput(button);
}

bool dae::Gamepad::IsButtonPressed(GamepadButton button) const
{
	return m_currentState.Gamepad.wButtons & GamepadButtonToXinput(button);
}

WORD dae::Gamepad::GamepadButtonToXinput(GamepadButton button) const
{
	switch (button)
	{
	case GamepadButton::A: return XINPUT_GAMEPAD_A;
	case GamepadButton::B: return XINPUT_GAMEPAD_B;
	case GamepadButton::X: return XINPUT_GAMEPAD_X;
	case GamepadButton::Y: return XINPUT_GAMEPAD_Y;
	case GamepadButton::START: return XINPUT_GAMEPAD_START;
	case GamepadButton::BACK: return XINPUT_GAMEPAD_BACK;
	case GamepadButton::LEFT_THUMB: return XINPUT_GAMEPAD_LEFT_THUMB;
	case GamepadButton::RIGHT_THUMB: return XINPUT_GAMEPAD_RIGHT_THUMB;
	case GamepadButton::LEFT_SHOULDER: return XINPUT_GAMEPAD_LEFT_SHOULDER;
	case GamepadButton::RIGHT_SHOULDER: return XINPUT_GAMEPAD_RIGHT_SHOULDER;
	case GamepadButton::DPAD_UP: return XINPUT_GAMEPAD_DPAD_UP;
	case GamepadButton::DPAD_DOWN: return XINPUT_GAMEPAD_DPAD_DOWN;
	case GamepadButton::DPAD_LEFT: return XINPUT_GAMEPAD_DPAD_LEFT;
	case GamepadButton::DPAD_RIGHT: return XINPUT_GAMEPAD_DPAD_RIGHT;
	default: return 0;
	}
}
