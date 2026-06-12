#include "Window.h"

#include <stdexcept>

void dae::Window::Init(int width, int height, const std::string& title)
{
	m_width = width;
	m_height = height;
	m_title = title;

	m_window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_OPENGL);

	if (m_window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}
}

void dae::Window::Destroy()
{
	if (m_window != nullptr)
	{
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	}
}

int dae::Window::GetWidth() const
{
	return m_width;
}

int dae::Window::GetHeight() const
{
	return m_height;
}

const std::string& dae::Window::GetTitle() const
{
	return m_title;
}

SDL_Window* dae::Window::GetSDLWindow() const
{
	return m_window;
}
