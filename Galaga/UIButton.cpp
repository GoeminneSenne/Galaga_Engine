#include "UIButton.h"


#include "EventArgs.h"
#include "EventQueue.h"
#include "GameObject.h"
#include "TextureRenderer.h"
#include "MenuComponent.h"

galaga::UIButton::UIButton(dae::GameObject* pOwner, MenuComponent* pMenu, const std::string& name)
	: Component(pOwner), m_pMenu(pMenu), m_name(name)
{
	m_pTextureRenderer = GetOwner()->GetComponent<dae::TextureRenderer>();
	if (m_pTextureRenderer != nullptr)
	{
		m_pTextureRenderer->SetSourceRect(m_normalSrcRect);
	}

	if (pMenu)
	{
		pMenu->RegisterButton(this);
	}
}

galaga::UIButton::~UIButton()
{
	if (m_pMenu)
	{
		m_pMenu->UnregisterButton(this);
	}
}

void galaga::UIButton::DetachMenu()
{
	m_pMenu = nullptr;
}

void galaga::UIButton::SetIsSelected(bool isSelected)
{
	m_isSelected = isSelected;

	if (m_pTextureRenderer)
	{
		if (m_isSelected)
			m_pTextureRenderer->SetSourceRect(m_selectedSrcRect);
		else
			m_pTextureRenderer->SetSourceRect(m_normalSrcRect);
	}
}

void galaga::UIButton::OnClick() const
{
	//TODO send event to eventQueue
	auto args = std::make_unique<ButtonClickedArgs>(m_name);
	dae::EventQueue::GetInstance().SendEvent(dae::make_sdbm_hash("ButtonClicked"), std::move(args));
}
