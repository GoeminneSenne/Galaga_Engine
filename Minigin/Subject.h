#pragma once
#include <vector>
#include <string>

#include "EventType.h"

namespace dae
{
	class GameObject;
	class Observer;

	class Subject
	{
	public:
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		void NotifyObservers(EventType eventType, GameObject* object) const;

	private:
		std::vector<Observer*> m_observers;
	};
}
