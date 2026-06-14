#include "EnemyComponent.h"

#include "Bullet.h"
#include "EnemyState.h"
#include "EventArgs.h"
#include "EventQueue.h"
#include "FormationManager.h"
#include "GameObject.h"
#include "TextureRenderer.h"

galaga::EnemyComponent::EnemyComponent(dae::GameObject* pOwner, const glm::vec3& formationPos,
                                       EnemyType* pType)
	: Component(pOwner)
	, m_formationPosition(formationPos)
	, m_state(std::make_unique<EntryState>(formationPos))
	, m_pType(pType)
{
	m_state->OnEnter(this);

	dae::TextureRenderer* pTextureRenderer = pOwner->GetComponent<dae::TextureRenderer>();
	if (pTextureRenderer)
	{
		pTextureRenderer->SetSourceRect(pType->GetSourceRect());
		pTextureRenderer->SetDestinationSize(32.f, 32.f);
	}
}

void galaga::EnemyComponent::Update(float deltaTime)
{
	auto newState{ m_state->Update(deltaTime, this) };
	if (newState)
	{
		m_state->OnExit(this);
		m_state = std::move(newState);
		m_state->OnEnter(this);
	}
}

void galaga::EnemyComponent::OnCollision(dae::GameObject* other)
{
	if (other->HasComponent<dae::Bullet>())
	{
		dae::EventQueue::GetInstance().SendEvent(dae::make_sdbm_hash("EnemyDestroyed"), std::make_unique<EnemyDestroyedArgs>(m_pType->GetFormationScore()));

		//TODO: finish implementation
		GetOwner()->Destroy();

	}

}

void galaga::EnemyComponent::Move(const glm::vec3& movement)
{
	glm::vec3 pos = GetOwner()->GetTransform()->GetLocalPosition();
	pos += movement;
	GetOwner()->GetTransform()->SetLocalPosition(pos);
}

glm::vec3 galaga::EnemyComponent::GetWorldPosition() const
{
	return GetOwner()->GetTransform()->GetWorldPosition();
}

glm::vec3 galaga::EnemyComponent::GetFormationPosition() const
{
	return m_formationPosition;
}
