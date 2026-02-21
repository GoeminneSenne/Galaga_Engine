#pragma once

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		void Destroy();

		virtual void Update(float deltaTime);
		virtual void FixedUpdate(float fixedTimeStep);
		virtual void Render() const;

		bool GetPendingDestroy() const;

		virtual ~Component() = default;


	protected:
		explicit Component(GameObject* pOwner);
		GameObject* GetOwner() const;

	private:
		GameObject* const m_pOwner;

		bool m_pendingDestroy{ false };
	};
}