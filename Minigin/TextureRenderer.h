#pragma once

#include <memory>
#include "Component.h"
#include "SDL3/SDL_oldnames.h"
#include "SDL3/SDL_rect.h"

namespace dae
{
	class Texture2D;
	class TextureRenderer : public Component
	{
	public:
		explicit TextureRenderer(GameObject* pOwner);
		explicit TextureRenderer(GameObject* pOwner, const std::string& filename);

		virtual void Render() const override;

		void SetTexture(const std::string& filename);
		void SetTexture(const std::shared_ptr<Texture2D>& pTexture);
		void SetSourceRect(float x, float y, float width, float height);
		void SetSourceRect(const SDL_FRect& srcRect);
		void SetDestinationSize(float width, float height);
	private:
		std::shared_ptr<Texture2D> m_texture{};
		SDL_FRect m_srcRect{0,0,-1,-1};
		float m_width{};
		float m_height{};
	};
}
