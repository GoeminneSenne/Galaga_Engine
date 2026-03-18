#pragma once
#include <string>

#include "EventType.h"
#include "GameObject.h"

namespace dae
{
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(EventType eventType, GameObject* object) = 0;
	};
}
