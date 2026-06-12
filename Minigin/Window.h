#pragma once

#include <string>
#include <SDL3/SDL.h>
#include "Singleton.h"

namespace dae
{
	/**
	* Simple RAII wrapper for the SDL Window
	*/
	class Window final : public Singleton<Window>
	{
	public:
		void Init(int width, int height, const std::string& title);
		void Destroy();

		int GetWidth() const;
		int GetHeight() const;
		const std::string& GetTitle() const;
		SDL_Window* GetSDLWindow() const;
	private:
		int m_width{ 1024 };
		int m_height{ 576 };
		std::string m_title{ "Title" };
		SDL_Window* m_window{};
	};
}