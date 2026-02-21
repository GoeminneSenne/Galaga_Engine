#include "FPS.h"
#include "GameObject.h"
#include "TextRenderer.h"
#include <string>
#include <cmath>

dae::FPS::FPS(GameObject* pOwner)
	:Component(pOwner)
{
}

void dae::FPS::Update(float deltaTime)
{
	++m_frameCount;
	m_elapsedTime += deltaTime;

	if (m_elapsedTime > 1.f)
	{
		m_currentFPS = static_cast<int>(static_cast<float>(m_frameCount) / m_elapsedTime);
		m_frameCount = 0;
		m_elapsedTime -= 1.f;

		auto* textRenderer = GetOwner()->GetComponent<TextRenderer>();
		textRenderer->SetText(std::to_string(m_currentFPS) + " FPS");
	}
}
