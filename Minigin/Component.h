#pragma once

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		explicit Component(GameObject* pOwner);
		virtual ~Component() = default;

		void Destroy();

		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render() const;

		GameObject* GetOwner() const;
		bool GetPendingDestroy() const;

	protected:
		GameObject* const m_pOwner;

		bool m_pendingDestroy{ false };
	};
}