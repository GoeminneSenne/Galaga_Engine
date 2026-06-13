#pragma once
#include <string>

#include "Component.h"
#include "SDL3/SDL_rect.h"

namespace dae
{
	class TextureRenderer;
}

namespace galaga
{
	class MenuComponent;

	class UIButton final : public dae::Component
	{
	public:
		explicit UIButton(dae::GameObject* pOwner, MenuComponent* pMenu, const std::string& name);
		~UIButton() override;

		void DetachMenu();
		void SetIsSelected(bool isSelected);

	private:
		MenuComponent* m_pMenu{};
		bool m_isSelected{ false };
		std::string m_name{};
		dae::TextureRenderer* m_pTextureRenderer{};
		constexpr static SDL_FRect m_normalSrcRect{ 0.f, 0.f, 60.f, 30.f };
		constexpr static SDL_FRect m_selectedSrcRect{ 0.f, 30.f, 60.f, 30.f };
	};
}
