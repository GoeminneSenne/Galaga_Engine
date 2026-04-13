#pragma once
#include "Event.h"

namespace dae
{
	class IEventListener
	{
	public:
		virtual void HandleEvent(const Event& event) = 0;

		IEventListener() = default;
		virtual ~IEventListener() = default;
		IEventListener(const IEventListener& other) = delete;
		IEventListener(IEventListener&& other) = delete;
		IEventListener& operator=(const IEventListener& other) = delete;
		IEventListener& operator=(IEventListener&& other) = delete;
	};
}
