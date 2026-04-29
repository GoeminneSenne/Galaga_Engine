#pragma once

#include <memory>
#include "Component.h"

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
	private:
		std::shared_ptr<Texture2D> m_texture{};
	};
}