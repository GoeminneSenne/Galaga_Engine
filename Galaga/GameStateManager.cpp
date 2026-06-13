#include "GameStateManager.h"

#include "EventQueue.h"
#include "Event.h"

void galaga::GameStateManager::Init()
{
	dae::EventQueue::GetInstance().Subscribe(this);

	m_currentState = std::make_unique<MainMenuState>();
	m_currentState->OnEnter(this);
}

void galaga::GameStateManager::HandleEvent(const dae::Event& event)
{
	auto newState = m_currentState->HandleEvent(this, event);
	if (newState != nullptr)
	{
		m_currentState->OnExit(this);
		m_currentState = std::move(newState);
		m_currentState->OnEnter(this);
	}
}
