#pragma once

#include <memory>
#include "Gamepad.h"

#include "InputBinding.h"

namespace dae
{
	enum class GamepadButton;
	class XInputGamepad : public Gamepad
	{
	public:
		explicit XInputGamepad(int gamepadIndex);
		~XInputGamepad() override;

		void Update() override;

		bool IsButtonDown(GamepadButton button) const override;
		bool IsButtonUp(GamepadButton button) const override;
		bool IsButtonPressed(GamepadButton button) const override;


	private:
		class XInputGamepadImpl;
		std::unique_ptr<XInputGamepadImpl> m_pImpl;


	};
}
