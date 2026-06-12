#include "LivesDisplay.h"

#include "GameObject.h"
#include "Lives.h"
#include "Renderer.h"
#include "ResourceManager.h"

dae::LivesDisplay::LivesDisplay(GameObject* pOwner, Lives* pLives)
	: Component{pOwner}
{
	if (pLives)
	{
		m_numLives = pLives->GetNumLives();
	}

	m_texture = ResourceManager::GetInstance().LoadTexture("Galaga.png");
}

void dae::LivesDisplay::Notify(EventId eventId, GameObject* object)
{
	if (eventId == make_sdbm_hash("PlayerDied"))
	{
		if (auto livesComp = object->GetComponent<Lives>())
		{
			m_numLives = livesComp->GetNumLives();
		}
	}
}

void dae::LivesDisplay::Render() const
{
	if (m_texture == nullptr) return;

	const auto& pos = GetOwner()->GetTransform()->GetWorldPosition();

	for (int idx{}; idx < m_numLives; ++idx)
	{
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x + ( m_size * static_cast<float>(idx)) , pos.y, m_size, m_size, m_srcRect);
	}
}
