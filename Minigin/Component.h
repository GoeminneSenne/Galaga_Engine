#pragma once

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		virtual void Update(float deltaTime);
		virtual void FixedUpdate(float fixedTimeStep);
		virtual void Render() const;

		void Destroy();
		bool GetPendingDestroy() const;

		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

	protected:
		explicit Component(GameObject* pOwner);
		GameObject* GetOwner() const;

	private:
		GameObject* const m_pOwner;

		bool m_pendingDestroy{ false };
	};
}