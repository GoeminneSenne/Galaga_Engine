#pragma once

namespace dae
{
	class GameObject
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(GameObject* object) = 0;
	};
}