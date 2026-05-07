#pragma once

#include <GameObjectCommand.h>
#include <glm/glm.hpp>

namespace dae
{
	class MoveObjectCommand : public GameObjectCommand
	{
	public: 
		MoveObjectCommand(GameObject* pObject, glm::vec3 direction, float speed);
		virtual ~MoveObjectCommand() override = default;

		virtual void Execute(float deltaTime) override;

	private:
		glm::vec3 m_direction;
		float m_speed;
	};
}
