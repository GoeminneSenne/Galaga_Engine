#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Scene.h"
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene();
		
		//TODO implement proper scene management (set current scene & change between scenes)
		Scene* GetCurrentScene() const;

		void Update(float deltaTime);
		void FixedUpdate(float fixedTimeStep);
		void Render();
		void RenderUI();
		void ProcessPendingDestroys();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::unique_ptr<Scene>> m_scenes{};
	};
}
