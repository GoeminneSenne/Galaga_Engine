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
		void Subscribe(IEventListener* listener);
		void Unsubscribe(IEventListener* listener);

		void SendEvent(EventId eventId, std::unique_ptr<EventArgs> args);

		void ProcessEvents();

	private:
		void Broadcast(const Event& event);

		std::queue<Event> m_queue;
		std::vector<IEventListener*> m_listeners;
	};
}