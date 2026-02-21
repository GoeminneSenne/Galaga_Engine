#include <algorithm>
#include "Scene.h"

using namespace dae;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	assert(object != nullptr && "Cannot add a null GameObject to the scene.");
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(const GameObject& object)
{
	for (auto& ptr : m_objects)
	{
		if (ptr.get() == &object)
		{
			ptr->Destroy();
			return;
		}
	}
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_objects)
	{
		object->Update(deltaTime);
	}
}

void dae::Scene::FixedUpdate(float fixedTimeStep)
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate(fixedTimeStep);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void dae::Scene::ProcessPendingDestroys()
{
	//Erase all pending GameObjects
	m_objects.erase(
		std::remove_if(
			m_objects.begin(),
			m_objects.end(),
			[](const auto& ptr) { return ptr->GetPendingDestroy(); }
		),
		m_objects.end()
	);

	//Check all remaining objects if components should be removed
	for (const auto& object : m_objects)
	{
		object->ProcessPendingDestroys();
	}
}

