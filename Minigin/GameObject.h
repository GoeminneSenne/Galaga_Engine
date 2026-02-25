#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Transform.h"
#include "Component.h"

namespace dae
{
	template<typename T>
	concept ComponentType = std::derived_from<T, Component>;

	class Texture2D;
	class GameObject final
	{
		Transform m_transform{this};
		std::vector<std::unique_ptr<Component>> m_components{};
		std::vector<GameObject*> m_children{};
		GameObject* m_pParent{ nullptr };
		bool m_pendingDestroy{ false };

		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
	public:
		void Update(float deltaTime);
		void FixedUpdate(float fixedTimeStep);
		void Render() const;

		Transform* GetTransform();
		void SetPosition(float x, float y);

		GameObject* GetParent() const;
		void SetParent(GameObject* pParent, bool keepWorldPosition = true);
		bool IsChild(GameObject* child) const;
		int GetChildCount() const;
		GameObject* GetChildAt(int index) const;
		const std::vector<GameObject*>& GetChildren() const;

		template<ComponentType T, typename...  Args>
			requires std::constructible_from<T, GameObject*, Args...>
		void AddComponent(Args&&... args);
		void RemoveComponent(const Component& component);
		template<ComponentType T>
		bool HasComponent() const;
		template<ComponentType T>
		T* GetComponent() const;

		void Destroy();
		bool GetPendingDestroy() const;
		void ProcessPendingDestroys();

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	};


	template <ComponentType T, typename ... Args>
	requires std::constructible_from<T, GameObject*, Args...>
	void GameObject::AddComponent(Args&&... args)
	{
		m_components.emplace_back(std::make_unique<T>(this, std::forward<Args>(args)...));
	}

	template<ComponentType T>
	bool GameObject::HasComponent() const
	{
		{
			for (const auto& component : m_components)
			{
				if (dynamic_cast<T*>(component.get()))
					return true;
			}

			return false;
		}
	}

	template<ComponentType T>
	T* GameObject::GetComponent() const
	{
		for (const auto& component : m_components)
		{
			if (auto castResult = dynamic_cast<T*>(component.get()))
				return castResult;
		};

		return nullptr;
	}
}
