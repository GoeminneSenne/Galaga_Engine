#include <string>
#include "TextureRenderer.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

dae::TextureRenderer::TextureRenderer(GameObject* pOwner, const std::string& filename)
	: Component(pOwner)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureRenderer::Render() const
{
	if (m_texture != nullptr)
	{
		const auto& pos = m_pOwner->GetTransform().GetPosition();
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
	}
}

void dae::TextureRenderer::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}
