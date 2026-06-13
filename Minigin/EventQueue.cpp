#include "EventQueue.h"

void dae::EventQueue::Subscribe(EventId eventId, IEventListener* listener)
{
	//Check if listener is already registered
	if (std::ranges::find(m_listenersV, listener) != m_listenersV.end()) return;

	//Look for an empty spot in current vector before increasing size
	auto itr = std::ranges::find(m_listenersV, nullptr);
	if (itr != m_listenersV.end())
	{
		*itr = listener;
		return;
	}

	//If there is no empty spot, extend vector
	m_listenersV.push_back(listener);
}

void dae::EventQueue::Unsubscribe(EventId, IEventListener* listener)
{
	//Set to nullpointer so iteration is not disrupted
	auto itr = std::ranges::find(m_listenersV, listener);
	if (itr != m_listenersV.end())
		*itr = nullptr;
}

void dae::EventQueue::ProcessPendingRemovals()
{
	while (! m_pendingUnsubscribes.empty())
	{
		const auto& [eventId, listener] = m_pendingUnsubscribes.front();
		//std::erase(m_listeners[eventId], listener);
		std::erase(m_listenersV, listener);
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
	for (auto* listener : m_listenersV)
	{
		if (listener != nullptr)
			listener->HandleEvent(event);
	}
}
