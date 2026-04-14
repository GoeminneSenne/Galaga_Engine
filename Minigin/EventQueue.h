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
		void Subscribe(EventId eventId, IEventListener* listener);
		void Unsubscribe(EventId eventId, IEventListener* listener);

		void SendEvent(EventId eventId, std::unique_ptr<EventArgs> args);

		void ProcessEvents();

	private:
		void Broadcast(const Event& event);

		std::queue<Event> m_queue;
		std::unordered_map<EventId, std::vector<IEventListener*>> m_listeners;
	};
}