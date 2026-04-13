#pragma once
#include <vector>
#include <string>

#include "Event.h"

namespace dae
{
	class GameObject;
	class IObserver;

	class Subject
	{
	public:
		void AddObserver(IObserver* observer);
		void RemoveObserver(IObserver* observer);
		void NotifyObservers(EventId eventId, GameObject* object) const;

	private:
		std::vector<IObserver*> m_observers;
	};
}
