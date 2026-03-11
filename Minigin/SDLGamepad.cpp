#include "SDLGamepad.h"

#include <vector>

#include "InputBinding.h"

#include <SDL3/SDL.h>

class dae::SDLGamepad::SDLGamepadImpl
{
public:
	explicit SDLGamepadImpl(int gamepadIndex) : m_gamepadIndex{gamepadIndex}
	{
		m_gamepad = SDL_OpenGamepad(gamepadIndex);

	}

	~SDLGamepadImpl() { if (m_gamepad) SDL_CloseGamepad(m_gamepad);}

	void Update();

	bool IsButtonDown(GamepadButton button) const;
	bool IsButtonUp(GamepadButton button) const;
	bool IsButtonPressed(GamepadButton button) const;

private:
	static std::uint32_t GamepadButtonToSDL(GamepadButton button);

	int m_gamepadIndex;
	SDL_Gamepad* m_gamepad{ nullptr };

	std::uint32_t m_currentState{};
	std::uint32_t m_previousState{};

	std::uint32_t m_buttonsPressedThisFrame{};
	std::uint32_t m_buttonsReleasedThisFrame{};
};

dae::SDLGamepad::SDLGamepad(int gamepadIndex)
	:m_pImpl(std::make_unique<SDLGamepadImpl>(gamepadIndex))
{}

void dae::SDLGamepad::SDLGamepadImpl::Update()
{
	m_previousState = m_currentState;

	for (int idx{0}; idx < SDL_GAMEPAD_BUTTON_COUNT; ++idx)
	{
		SDL_GamepadButton button = static_cast<SDL_GamepadButton>(idx);
		bool pressed = SDL_GetGamepadButton(m_gamepad, button);
		m_currentState |= ((int)pressed << idx);
	}

	std::uint32_t buttonChanges = m_currentState ^ m_previousState;
	m_buttonsPressedThisFrame = buttonChanges & m_currentState;
	m_buttonsReleasedThisFrame = buttonChanges & (~m_currentState);
}

bool dae::SDLGamepad::SDLGamepadImpl::IsButtonDown(GamepadButton button) const
{
	return m_buttonsPressedThisFrame & GamepadButtonToSDL(button);
}

bool dae::SDLGamepad::SDLGamepadImpl::IsButtonUp(GamepadButton button) const
{
	return m_buttonsReleasedThisFrame & GamepadButtonToSDL(button);
}

bool dae::SDLGamepad::SDLGamepadImpl::IsButtonPressed(GamepadButton button) const
{
	return m_currentState & GamepadButtonToSDL(button);
}

std::uint32_t dae::SDLGamepad::SDLGamepadImpl::GamepadButtonToSDL(GamepadButton button)
{
	int buttonIdx = -1;

	switch (button)
	{
	case GamepadButton::A: buttonIdx = SDL_GAMEPAD_BUTTON_SOUTH; break;
	case GamepadButton::B: buttonIdx = SDL_GAMEPAD_BUTTON_EAST; break;
	case GamepadButton::X: buttonIdx = SDL_GAMEPAD_BUTTON_WEST; break;
	case GamepadButton::Y: buttonIdx = SDL_GAMEPAD_BUTTON_NORTH; break;
	case GamepadButton::START: buttonIdx = SDL_GAMEPAD_BUTTON_START; break;
	case GamepadButton::BACK: buttonIdx = SDL_GAMEPAD_BUTTON_BACK; break;
	case GamepadButton::LEFT_THUMB: buttonIdx = SDL_GAMEPAD_BUTTON_LEFT_STICK; break;
	case GamepadButton::RIGHT_THUMB: buttonIdx = SDL_GAMEPAD_BUTTON_RIGHT_STICK; break;
	case GamepadButton::LEFT_SHOULDER: buttonIdx = SDL_GAMEPAD_BUTTON_LEFT_SHOULDER; break;
	case GamepadButton::RIGHT_SHOULDER: buttonIdx = SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER; break;
	case GamepadButton::DPAD_UP: buttonIdx = SDL_GAMEPAD_BUTTON_DPAD_UP; break;
	case GamepadButton::DPAD_DOWN: buttonIdx = SDL_GAMEPAD_BUTTON_DPAD_DOWN; break;
	case GamepadButton::DPAD_LEFT: buttonIdx = SDL_GAMEPAD_BUTTON_DPAD_LEFT; break;
	case GamepadButton::DPAD_RIGHT: buttonIdx = SDL_GAMEPAD_BUTTON_DPAD_RIGHT; break;
	default: SDL_GAMEPAD_BUTTON_INVALID;
	}

	if (buttonIdx == SDL_GAMEPAD_BUTTON_INVALID) return 0;

	return 1 << buttonIdx;
}

dae::SDLGamepad::~SDLGamepad() = default;

void dae::SDLGamepad::Update()
{
	m_pImpl->Update();
}

bool dae::SDLGamepad::IsButtonDown(GamepadButton button) const
{
	return m_pImpl->IsButtonDown(button);
}

bool dae::SDLGamepad::IsButtonUp(GamepadButton button) const
{
	return m_pImpl->IsButtonUp(button);
}

bool dae::SDLGamepad::IsButtonPressed(GamepadButton button) const
{
	return m_pImpl->IsButtonPressed(button);
}

