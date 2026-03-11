#pragma once
#include <vector>

#include "Singleton.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

	private:
		const bool* m_currentKeyboardState{};
		std::vector<bool> m_previousKeyboardState;
		int m_numKeys{};
	};

}
