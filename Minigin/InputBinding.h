#pragma once
#include <memory>
#include <SDL3/SDL.h>
#include "ICommand.h"

namespace dae
{
	enum class KeyState
	{
		Down,
		Up,
		Pressed
	};

	struct Keybind
	{
		SDL_Scancode key;
		KeyState state;
		std::unique_ptr<ICommand> pCommand;
	};

	enum class GamepadButton
	{
		A,
		B,
		X,
		Y,
		START,
		BACK,
		LEFT_THUMB,
		RIGHT_THUMB,
		LEFT_SHOULDER,
		RIGHT_SHOULDER,
		DPAD_UP,
		DPAD_DOWN,
		DPAD_LEFT,
		DPAD_RIGHT
	};

	struct ButtonBind
	{
		GamepadButton button;
		int gamepadIndex;
		KeyState state;
		std::unique_ptr<ICommand> pCommand;
	};

}
