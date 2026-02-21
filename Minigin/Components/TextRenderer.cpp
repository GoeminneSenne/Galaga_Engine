#include <stdexcept>
#include <SDL3_ttf/SDL_ttf.h>
#include "TextRenderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "Renderer.h"

dae::TextRenderer::TextRenderer(GameObject* pOwner, const std::string& text,
	std::shared_ptr<Font> font, const SDL_Color& color)
	: Component(pOwner), m_needsUpdate{true}, 
	m_text{text}, m_color(color), m_font(std::move(font)), m_textTexture{nullptr}
{}

void dae::TextRenderer::Update(float)
{
	if (m_needsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_text.length(), m_color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_DestroySurface(surf);
		m_textTexture = std::make_shared<Texture2D>(texture);
		m_needsUpdate = false;
	}
}

void dae::TextRenderer::Render() const
{
	if (m_textTexture != nullptr)
	{
		const auto& pos = GetOwner()->GetTransform().GetPosition();
		Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
	}
}

void dae::TextRenderer::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}

void dae::TextRenderer::SetColor(const SDL_Color& color)
{
	m_color = color;
	m_needsUpdate = true;
}
