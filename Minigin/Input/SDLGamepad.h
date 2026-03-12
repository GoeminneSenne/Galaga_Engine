#pragma once

#include <memory>

#include "Gamepad.h"


namespace dae
{
	class SDLGamepad : public Gamepad
	{
	public:
		explicit SDLGamepad(int gamepadIndex);
		~SDLGamepad() override;

		void Update() override;

		bool IsButtonDown(GamepadButton button) const override;
		bool IsButtonUp(GamepadButton button) const override;
		bool IsButtonPressed(GamepadButton button) const override;
	
	private:
		class SDLGamepadImpl;
		std::unique_ptr<SDLGamepadImpl> m_pImpl;
	};
}