#pragma once

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		explicit Component(const GameObject* pOwner);

	protected:
		const GameObject* const m_pOwner;

	};
}