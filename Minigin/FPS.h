#pragma once
#include "Component.h"

namespace dae
{
	class FPS : public Component
	{
	public:
		explicit FPS(GameObject* pOwner);

		virtual void Update(float deltaTime) override;
	private:
		int m_frameCount{};
		float m_elapsedTime{};
		float m_currentFPS{};
	};
}