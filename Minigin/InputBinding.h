#pragma once
#include <memory>
#include <SDL3/SDL.h>
#include "Command.h"

namespace dae
{
	class Command;

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
		std::unique_ptr<Command> pCommand;
	};

	struct ButtonBind
	{
		unsigned int button;
		KeyState state;
		std::unique_ptr<Command> pCommand;
	};

}
