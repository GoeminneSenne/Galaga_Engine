#include "EventQueue.h"

void dae::EventQueue::Subscribe(EventId eventId, IEventListener* listener)
{
	//TODO: check if listener is already in vector
	m_listeners[eventId].push_back(listener);
}

void dae::EventQueue::Unsubscribe(EventId, IEventListener*)
{
	//TODO
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
