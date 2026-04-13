#pragma once
#include <string>

#include "EventType.h"
#include "GameObject.h"

namespace dae
{
	class IObserver
	{
	public:
		virtual ~IObserver() = default;
		virtual void Notify(EventType eventType, GameObject* object) = 0;
	};
}
