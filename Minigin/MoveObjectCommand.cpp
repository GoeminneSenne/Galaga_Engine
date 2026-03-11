#include "MoveObjectCommand.h"

#include "GameObject.h"

dae::MoveObjectCommand::MoveObjectCommand(GameObject* pObject, glm::vec3 direction, float speed)
	: GameObjectCommand{ pObject }, m_direction{ direction }, m_speed{ speed }
{}

void dae::MoveObjectCommand::Execute()
{
	auto oldPos = GetGameObject()->GetTransform()->GetLocalPosition();
	auto newPos = oldPos + m_direction * m_speed;

	GetGameObject()->GetTransform()->SetLocalPosition(newPos);
}
