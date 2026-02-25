#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class GameObject;

	class Transform final
	{
	public:
		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(float x, float y, float z = 0);
		void SetPosition(const glm::vec3& position);
	
	
		explicit Transform(GameObject* pOwner);
		//TODO: add Rule of 5?
	private:
		GameObject* const m_pOwner{};

		glm::vec3 m_position; //TODO: add cached WorldPosition so you don't need to recalc
		bool m_isPositionDirty{true};
	};
}
