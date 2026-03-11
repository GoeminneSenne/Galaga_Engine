#pragma once

namespace dae
{
	enum class GamepadButton;
	class Gamepad
	{
	public:
		explicit Gamepad(int gamepadIndex) : m_gamepadIndex{ gamepadIndex } {}
		virtual ~Gamepad() = default;

		virtual void Update() = 0;

		virtual bool IsButtonDown(GamepadButton button) const = 0;
		virtual bool IsButtonUp(GamepadButton button) const = 0;
		virtual bool IsButtonPressed(GamepadButton button) const = 0;


	protected:
		int m_gamepadIndex;
	};
}
