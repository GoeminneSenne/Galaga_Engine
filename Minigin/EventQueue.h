#pragma once

#include <queue>

#include "Event.h"
#include "Singleton.h"

namespace dae
{
	class EventQueue : public Singleton<EventQueue>
	{
	public:

	private:
		std::queue<Event> m_queue;
	};
}