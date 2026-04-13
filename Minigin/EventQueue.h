#pragma once

#include <queue>
#include <unordered_map>

#include "Event.h"
#include "IEventListener.h"
#include "Singleton.h"

namespace dae
{
	class EventQueue : public Singleton<EventQueue>
	{
	public:

	private:
		std::queue<Event> m_queue;
		std::unordered_map<EventId, std::vector<IEventListener*>> m_listeners;
	};
}