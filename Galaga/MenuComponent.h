#pragma once
#include <Component.h>
#include <vector>
#include "UIButton.h"

namespace galaga
{
	class MenuComponent final : public dae::Component
	{
	public:
		explicit MenuComponent(dae::GameObject* pOwner);
		~MenuComponent() override;

		void RegisterButton(UIButton* button);
		void UnregisterButton(UIButton* button);

		void SelectNextButton();
		void SelectPreviousButton();
		void ClickSelectedButton();

	private:
		std::vector<UIButton*> m_buttons;
		int m_selectedButton{};
	};
}
