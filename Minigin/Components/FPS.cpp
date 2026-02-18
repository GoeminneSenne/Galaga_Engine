#include "FPS.h"

dae::FPS::FPS(GameObject* pOwner)
	:Component(pOwner)
{
}

void dae::FPS::Update(float deltaTime)
{
	++m_frameCount;
	m_elapsedTime += deltaTime;

	if (m_elapsedTime >= 1.f)
	{
		m_currentFPS = static_cast<float>(m_frameCount) / m_elapsedTime;
		m_frameCount = 0;
		m_elapsedTime -= 1.f;
	}
}
