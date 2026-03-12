#include "XInputGamepad.h"
#include "InputBinding.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <Xinput.h>

class dae::XInputGamepad::XInputGamepadImpl
{
public:
	explicit XInputGamepadImpl(int gamepadIndex) : m_gamepadIndex{ gamepadIndex } {}
	~XInputGamepadImpl() = default;

	void Update();

	bool IsButtonDown(GamepadButton button) const;
	bool IsButtonUp(GamepadButton button) const;
	bool IsButtonPressed(GamepadButton button) const;
private:
	static WORD GamepadButtonToXinput(GamepadButton button);

	int m_gamepadIndex;

	XINPUT_STATE m_previousState{};
	XINPUT_STATE m_currentState{};

	WORD m_buttonsPressedThisFrame{};
	WORD m_buttonsReleasedThisFrame{};
};

void dae::XInputGamepad::XInputGamepadImpl::Update()
{
	CopyMemory(&m_previousState, &m_currentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_currentState, sizeof(XINPUT_STATE));
	XInputGetState(m_gamepadIndex, &m_currentState);

	WORD buttonChanges = m_currentState.Gamepad.wButtons ^ m_previousState.Gamepad.wButtons;
	m_buttonsPressedThisFrame = buttonChanges & m_currentState.Gamepad.wButtons;
	m_buttonsReleasedThisFrame = buttonChanges & (~m_currentState.Gamepad.wButtons);
}

bool dae::XInputGamepad::XInputGamepadImpl::IsButtonDown(GamepadButton button) const
{
	return m_buttonsPressedThisFrame & GamepadButtonToXinput(button);
}

bool dae::XInputGamepad::XInputGamepadImpl::IsButtonUp(GamepadButton button) const
{
	return m_buttonsReleasedThisFrame & GamepadButtonToXinput(button);
}

bool dae::XInputGamepad::XInputGamepadImpl::IsButtonPressed(GamepadButton button) const
{
	return m_currentState.Gamepad.wButtons & GamepadButtonToXinput(button);
}

WORD dae::XInputGamepad::XInputGamepadImpl::GamepadButtonToXinput(GamepadButton button)
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

dae::XInputGamepad::XInputGamepad(int gamepadIndex)
	:m_pImpl{ std::make_unique<XInputGamepadImpl>(gamepadIndex) }
{
}

dae::XInputGamepad::~XInputGamepad() = default;

void dae::XInputGamepad::Update()
{
	m_pImpl->Update();
}

bool dae::XInputGamepad::IsButtonDown(GamepadButton button) const
{
	return m_pImpl->IsButtonDown(button);
}

bool dae::XInputGamepad::IsButtonUp(GamepadButton button) const
{
	return m_pImpl->IsButtonUp(button);
}

bool dae::XInputGamepad::IsButtonPressed(GamepadButton button) const
{
	return m_pImpl->IsButtonPressed(button);
}
