#include "Component.h"

using namespace dae;

Component::Component(GameObject* pOwner)
	:m_pOwner{pOwner}
{
}

void dae::Component::Update()
{
}

void dae::Component::Render() const
{
}

GameObject* dae::Component::GetOwner() const
{
	return m_pOwner;
}

