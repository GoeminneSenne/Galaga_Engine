#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class GameObject;

	class Transform final
	{
	public:
		[[nodiscard]] const glm::vec3& GetLocalPosition() const;
		void SetLocalPosition(float x, float y, float z = 0);
		void SetLocalPosition(const glm::vec3& position);
	
		[[nodiscard]] const glm::vec3& GetWorldPosition();
		
		void SetPositionDirty();

		explicit Transform(GameObject* pOwner);
		~Transform() = default;
		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;
	private:
		void UpdateWorldPosition();

		GameObject* const m_pOwner{};

		glm::vec3 m_localPosition{};
		glm::vec3 m_worldPosition{};
		bool m_isPositionDirty{true};
	};
}
