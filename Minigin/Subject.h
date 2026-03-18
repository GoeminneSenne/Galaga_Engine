#pragma once
#include <vector>
#include <string>

namespace dae
{
	class GameObject;
	class Observer;

	class Subject
	{
	public:
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		void NotifyObservers(const std::string& eventId, GameObject* object) const;

	private:
		std::vector<Observer*> m_observers;
	};
}
