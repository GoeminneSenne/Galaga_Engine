#pragma once
#include <string>

namespace dae
{
	class GameObject;
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(const std::string& event, GameObject* object) = 0;
	};
}
