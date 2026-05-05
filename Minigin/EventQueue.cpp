#include "EventQueue.h"

void dae::EventQueue::Subscribe(EventId eventId, IEventListener* listener)
{
	if (std::ranges::find(m_listeners[eventId], listener) != m_listeners[eventId].end()) return;

	m_listeners[eventId].push_back(listener);
}

void dae::EventQueue::Unsubscribe(EventId eventId, IEventListener* listener)
{
	m_pendingUnsubscribes.emplace(eventId, listener);
}

void dae::EventQueue::ProcessPendingRemovals()
{
	while (! m_pendingUnsubscribes.empty())
	{
		const auto& [eventId, listener] = m_pendingUnsubscribes.front();
		std::erase(m_listeners[eventId], listener);
		m_pendingUnsubscribes.pop();
	}
}

void dae::EventQueue::SendEvent(EventId eventId, std::unique_ptr<EventArgs> args)
{
	m_queue.emplace(eventId, std::move(args));
}

void dae::EventQueue::ProcessEvents()
{
	while (!m_queue.empty())
	{
		Event event = std::move(m_queue.front());
		m_queue.pop();

		Broadcast(event);
	}
}

void dae::EventQueue::Broadcast(const Event& event)
{
	for (auto* listener : m_listeners[event.id])
	{
		listener->HandleEvent(event);
	}
}
