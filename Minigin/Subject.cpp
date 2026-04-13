#include "Subject.h"
#include "IObserver.h"

void dae::Subject::AddObserver(IObserver* observer)
{
	m_observers.push_back(observer);
}

void dae::Subject::RemoveObserver(IObserver* observer)
{
	std::erase(m_observers, observer);
}

void dae::Subject::NotifyObservers(EventId eventId, GameObject* object) const
{
	for (auto observer : m_observers)
	{
		observer->Notify(eventId, object);
	}
}
