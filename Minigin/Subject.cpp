#include "Subject.h"
#include "Observer.h"

void dae::Subject::AddObserver(Observer* observer)
{
	m_observers.push_back(observer);
}

void dae::Subject::RemoveObserver(Observer* observer)
{
	std::erase(m_observers, observer);
}

void dae::Subject::NotifyObservers(EventType eventType, GameObject* object) const
{
	for (auto observer : m_observers)
	{
		observer->Notify(eventType, object);
	}
}
