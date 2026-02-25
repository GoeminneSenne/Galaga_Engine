#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class GameObject;

	class Transform final
	{
	public:
		const glm::vec3& GetLocalPosition() const;
		void SetLocalPosition(float x, float y, float z = 0);
		void SetLocalPosition(const glm::vec3& position);
	
		const glm::vec3& GetWorldPosition();

		explicit Transform(GameObject* pOwner);
		//TODO: add Rule of 5?
	private:
		void SetPositionDirty();
		void UpdateWorldPosition();

		GameObject* const m_pOwner{};

		glm::vec3 m_localPosition{};
		glm::vec3 m_worldPosition{};
		bool m_isPositionDirty{true};
	};
}
