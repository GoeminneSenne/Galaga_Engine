#include "Bullet.h"

#include "EnemyComponent.h"
#include "EventQueue.h"
#include "GameObject.h"
#include "TextureRenderer.h"

dae::Bullet::Bullet(GameObject* pOwner, const glm::vec3& position)
	: Component(pOwner)
{
	GetOwner()->GetTransform()->SetLocalPosition(position);

	auto texture = GetOwner()->GetComponent<TextureRenderer>();
	texture->SetSourceRect(m_srcRect);
	texture->SetDestinationSize(m_width, m_height);
}

void dae::Bullet::Update(float deltaTime)
{
	m_currentLifetime += deltaTime;
	if (m_currentLifetime >= m_maxLifetime)
	{
		auto args = std::make_unique<BulletDestroyedArgs>();
		args->hasHitEnemy = false;
		EventQueue::GetInstance().SendEvent(make_sdbm_hash("BulletDestroyed"), std::move(args));

		GetOwner()->Destroy();
	}


	glm::vec3 pos = GetOwner()->GetTransform()->GetLocalPosition();
	pos += glm::vec3(0.f, -m_speed * deltaTime, 0.f);
	GetOwner()->GetTransform()->SetLocalPosition(pos);
}

void dae::Bullet::OnCollision(GameObject* other)
{
	if (other->HasComponent<galaga::EnemyComponent>())
	{
		//TODO finish implementation
		GetOwner()->Destroy();
	}
}

