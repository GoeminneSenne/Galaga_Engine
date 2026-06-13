#include <string>
#include "TextureRenderer.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

dae::TextureRenderer::TextureRenderer(GameObject* pOwner)
	: Component(pOwner)
{
}

dae::TextureRenderer::TextureRenderer(GameObject* pOwner, const std::string& filename)
	: Component(pOwner)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureRenderer::Render() const
{
	if (m_texture == nullptr) return;

		
	const auto& pos = GetOwner()->GetTransform()->GetWorldPosition();
	if (SDL_RectEmptyFloat(&m_srcRect))
	{
		if (m_width == 0 && m_height == 0)
		{
			Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
		}
		else
		{
			Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y, m_width, m_height);
		}

	}
	else
	{
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y, m_width, m_height, m_srcRect);
	}

}

void dae::TextureRenderer::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureRenderer::SetTexture(const std::shared_ptr<Texture2D>& pTexture)
{
	m_texture = pTexture;
}

void dae::TextureRenderer::SetSourceRect(float x, float y, float width, float height)
{
	m_srcRect.x = x;
	m_srcRect.y = y;
	m_srcRect.w = width;
	m_srcRect.h = height;
}

void dae::TextureRenderer::SetSourceRect(const SDL_FRect& srcRect)
{
	m_srcRect = srcRect;
}

void dae::TextureRenderer::SetDestinationSize(float width, float height)
{
	m_width = width;
	m_height = height;
}
