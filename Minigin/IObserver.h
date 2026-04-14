#pragma once
#include <string>

#include "Event.h"
#include "GameObject.h"

namespace dae
{
	class IObserver
	{
	public:
		virtual void Notify(EventId eventId, GameObject* object) = 0;

		IObserver() = default;
		virtual ~IObserver() = default;
		IObserver(const IObserver& other) = delete;
		IObserver(IObserver&& other) = delete;
		IObserver& operator=(const IObserver& other) = delete;
		IObserver& operator=(IObserver&& other) = delete;
	};
}
