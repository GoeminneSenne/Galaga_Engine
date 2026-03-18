#pragma once
#include <vector>

namespace dae
{
	class GameObject;
	class Observer;

	class Subject
	{
	public:
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		void NotifyObservers(GameObject* object) const;

	private:
		std::vector<Observer*> m_observers;
	};
}
