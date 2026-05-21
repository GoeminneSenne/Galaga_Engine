#pragma once

namespace dae
{
	enum class GamepadButton;
	class Gamepad
	{
	public:
		virtual ~Gamepad();

		virtual void Update() = 0;

		virtual bool IsButtonDown(GamepadButton button) const = 0;
		virtual bool IsButtonUp(GamepadButton button) const = 0;
		virtual bool IsButtonPressed(GamepadButton button) const = 0;
	};
}
