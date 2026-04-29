#pragma once

#include "ICommand.h"

namespace dae
{
	class GameObject;
	
	class GameObjectCommand : public ICommand
	{
	public:
		GameObjectCommand(GameObject* pObject) : m_pObject{ pObject } {}
		virtual ~GameObjectCommand() override = default;

	protected:
		GameObject* GetGameObject() const { return m_pObject; }

	private:
		GameObject* m_pObject;
	};
};
