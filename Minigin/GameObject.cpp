#include <string>
#include <ranges>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (auto& component : m_components)
	{
		component->Update();
	}
}

void dae::GameObject::Render() const
{
	const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::AddComponent(std::unique_ptr<Component> component)
{
	assert(component != nullptr && "Cannot add a null Component to gameobject");
	m_components.emplace_back(std::move(component));
}

void dae::GameObject::RemoveComponent(const Component& component)
{
	for (auto& ptr : m_components)
	{
		if (ptr.get() == &component)
		{
			ptr->Destroy();
		}
	}
}

void dae::GameObject::ProcessPendingDestroys()
{
	m_components.erase(
		std::remove_if(
			m_components.begin(),
			m_components.end(),
			[](const auto& component) {return component->GetPendingDestroy(); }
		),
		m_components.end()
	);
}

