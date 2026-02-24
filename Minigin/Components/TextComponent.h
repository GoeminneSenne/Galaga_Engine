#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include <memory>
#include <string>
#include "Component.h"


namespace dae
{
	class TextureRenderer;
	class Font;
	class Texture2D;
	class TextComponent : public Component
	{
	public:
		explicit TextComponent(GameObject* pOwner, const std::string& text,
			std::shared_ptr<Font> font, const SDL_Color& color = { 255,255,255,255 });

		virtual void Update(float deltaTime) override;

		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color);

	private:
		bool m_needsUpdate{};
		std::string m_text{};
		SDL_Color m_color{ 255, 255, 255, 255 };
		std::shared_ptr<Font> m_font{};
		TextureRenderer* m_pTextureRenderer{};
	};
}