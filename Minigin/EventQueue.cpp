#include "EventQueue.h"

void dae::EventQueue::Subscribe(IEventListener* listener)
{
	//Check if listener is already registered
	if (std::ranges::find(m_listeners, listener) != m_listeners.end()) return;

	//Look for an empty spot in current vector before increasing size
	auto itr = std::ranges::find(m_listeners, nullptr);
	if (itr != m_listeners.end())
	{
		*itr = listener;
		return;
	}

	//If there is no empty spot, extend vector
	m_listeners.push_back(listener);
}

void dae::EventQueue::Unsubscribe(IEventListener* listener)
{
	//Set to nullptr so iteration is not disrupted
	auto itr = std::ranges::find(m_listeners, listener);
	if (itr != m_listeners.end())
		*itr = nullptr;
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
	for (auto* listener : m_listeners)
	{
		if (listener != nullptr)
			listener->HandleEvent(event);
	}
}
