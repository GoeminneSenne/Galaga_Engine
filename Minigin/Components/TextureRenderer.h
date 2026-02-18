#pragma once

#include <memory>
#include "Component.h"

namespace dae
{
	class Texture2D;
	class TextureRenderer : public Component
	{
	public:
		explicit TextureRenderer(GameObject* pOwner, const std::string& filename);

		virtual void Render() const override;

		void SetTexture(const std::string& filename);
	private:
		std::shared_ptr<Texture2D> m_texture{};
	};
}