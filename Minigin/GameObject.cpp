#include <string>
#include <ranges>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;


void dae::GameObject::AddChild(GameObject* child)
{
	m_children.push_back(child);
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	std::erase(m_children, child);
}

void dae::GameObject::Update(float deltaTime)
{
	for (auto& component : m_components)
	{
		component->Update(deltaTime);
	}
}

void dae::GameObject::FixedUpdate(float fixedTimeStep)
{
	for (auto& component : m_components)
	{
		component->FixedUpdate(fixedTimeStep);
	}
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_components)
	{
		component->Render();
	}
}

dae::Transform* dae::GameObject::GetTransform()
{
	return &m_transform;
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetLocalPosition(x, y, 0.0f);
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_pParent;
}

void dae::GameObject::SetParent(GameObject* pParent, bool keepWorldPosition)
{
	if (IsChild(pParent) || pParent == this || pParent == m_pParent)
		return;
	
	if (pParent == nullptr)
	{
		
	}
	else
	{
		if (keepWorldPosition)
		{
			
		}
		
	}

	if (m_pParent)
		m_pParent->RemoveChild(this);
	m_pParent = pParent;
	if (m_pParent)
		m_pParent->AddChild(this);
}

bool dae::GameObject::IsChild(GameObject* child) const
{
	return (std::ranges::count(m_children, child) > 0);
}

int dae::GameObject::GetChildCount() const
{
	return static_cast<int>(m_children.size());
}

dae::GameObject* dae::GameObject::GetChildAt(int index) const
{
	if (index < 0 || static_cast<size_t>(index) > m_children.size()) return nullptr;

	return m_children[index];
}

const std::vector<dae::GameObject*>& dae::GameObject::GetChildren() const
{
	return m_children;
}

void dae::GameObject::RemoveComponent(const Component& component)
{
	for (auto& ptr : m_components)
	{
		if (ptr.get() == &component)
		{
			ptr->Destroy();
			return;
		}
	}
}

void dae::GameObject::ProcessPendingDestroys()
{
	m_components.erase(
		std::ranges::remove_if(m_components,
			[](const auto& component) {return component->GetPendingDestroy(); }
		).begin(),
		m_components.end()
	);
}

void dae::GameObject::Destroy()
{
	m_pendingDestroy = true;
}

bool dae::GameObject::GetPendingDestroy() const
{
	return m_pendingDestroy;
}

