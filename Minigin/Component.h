#pragma once

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		explicit Component(GameObject* pOwner);
		virtual ~Component() = default;
		
		virtual void Update();
		virtual void Render() const;

		GameObject* GetOwner() const;

	protected:
		GameObject* const m_pOwner;

	};
}