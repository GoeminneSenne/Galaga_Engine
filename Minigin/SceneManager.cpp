#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{
	m_scene->Update(deltaTime);
	/*
	for(auto& scene : m_scenes)
	{
		scene->Update(deltaTime);
	}
*/
}

void dae::SceneManager::FixedUpdate(float fixedTimeStep)
{
	m_scene->FixedUpdate(fixedTimeStep);

	/*
	for (auto& scene : m_scenes)
	{
		scene->FixedUpdate(fixedTimeStep);
	}
	 */
}

void dae::SceneManager::Render()
{
	m_scene->Render();
	/*
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
	 */
}

void dae::SceneManager::RenderUI()
{
	m_scene->RenderUI();

	/*
	for (const auto& scene : m_scenes)
	{
		scene->RenderUI();
	}
	 */
}

void dae::SceneManager::ProcessPendingDestroys()
{
	m_scene->ProcessPendingDestroys();
	/*
	for (auto& scene : m_scenes)
	{
		scene->ProcessPendingDestroys();
	}
	*/
}

dae::Scene& dae::SceneManager::CreateScene()
{
	m_scene = std::unique_ptr<Scene>(new Scene());
	return *m_scene;

	//m_scenes.emplace_back(new Scene());
	//return *m_scenes.back();
}

//TODO Implement proper scene management
dae::Scene* dae::SceneManager::GetCurrentScene() const
{
	return m_scene.get();
	//return m_scenes[0].get();
}
