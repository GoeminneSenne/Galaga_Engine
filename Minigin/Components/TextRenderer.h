#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include <memory>
#include <string>
#include "Component.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextRenderer : public Component
	{
	public:
		explicit TextRenderer(GameObject* pOwner, const std::string& text,
			std::shared_ptr<Font> font, const SDL_Color& color = { 255,255,255,255 });

		virtual void Update(float deltaTime) override;
		virtual void Render() const override;

		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color);

	private:
		bool m_needsUpdate{};
		std::string m_text{};
		SDL_Color m_color{ 255, 255, 255, 255 };
		std::shared_ptr<Font> m_font{};
		std::shared_ptr<Texture2D> m_textTexture{};
	};
}