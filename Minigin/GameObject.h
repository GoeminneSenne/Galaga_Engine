#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Transform.h"
#include "Component.h"

namespace dae
{
	class Texture2D;
	class GameObject final
	{
		Transform m_transform{};
		std::vector<std::unique_ptr<Component>> m_components{};
		bool m_pendingDestroy{ false };
	public:
		void Update(float deltaTime);
		void FixedUpdate(float fixedTimeStep);
		void Render() const;

		Transform GetTransform() const;
		void SetPosition(float x, float y);

		void AddComponent(std::unique_ptr<Component> component);
		void RemoveComponent(const Component& component);
		template<typename T>
		bool HasComponent() const;
		template<typename T>
		T* GetComponent();

		void Destroy();
		bool GetPendingDestroy() const;
		void ProcessPendingDestroys();

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	};


	template<typename T>
	inline bool GameObject::HasComponent() const
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

	template<typename T>
	inline T* GameObject::GetComponent()
	{
		for (const auto& component : m_components)
		{
			if (auto castResult = dynamic_cast<T*>(component.get()))
				return castResult;
		};

		return nullptr;
	}
}
