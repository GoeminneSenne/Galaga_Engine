#include "Component.h"

using namespace dae;

Component::Component(GameObject* pOwner)
	:m_pOwner{pOwner}
{
}

void dae::Component::Destroy()
{
	m_pendingDestroy = true;
}

void dae::Component::Update(float)
{
}

void dae::Component::FixedUpdate(float)
{
}

void dae::Component::Render() const
{
}

GameObject* dae::Component::GetOwner() const
{
	return m_pOwner;
}

bool dae::Component::GetPendingDestroy() const
{
	return m_pendingDestroy;
}

