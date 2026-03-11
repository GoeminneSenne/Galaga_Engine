#pragma once
#include <SDL3/SDL.h>


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
	};
}
