#include "PlayerShip.h"

#include <memory>
#include <Event.h>
#include <EventQueue.h>

#include "Bullet.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "TextureRenderer.h"


dae::PlayerShip::PlayerShip(GameObject* pOwner)
	: Component(pOwner)
{
	auto texture = GetOwner()->GetComponent<TextureRenderer>();
	texture->SetSourceRect(m_srcRect);
	texture->SetDestinationSize(m_width, m_height);

	EventQueue::GetInstance().Subscribe(make_sdbm_hash("BulletDestroyed"), this);
}

dae::PlayerShip::~PlayerShip()
{
	EventQueue::GetInstance().Unsubscribe(make_sdbm_hash("BulletDestroyed"), this);
}

void dae::PlayerShip::Update(float deltaTime)
{
	if (m_currentCooldown > 0.f)
	{
		m_currentCooldown -= deltaTime;
	}
}

void dae::PlayerShip::HandleEvent(const Event& event)
{
	if (event.id == make_sdbm_hash("BulletDestroyed"))
	{
		--m_activeBullets;
	}
}

void dae::PlayerShip::ShootBullet()
{
	//SFX
	ServiceLocator::GetSoundSystem().PlaySFX("./Data/PlayerShoot.mp3", 0.1f);

	//Create Object
	auto bulletObj = std::make_unique<dae::GameObject>();
	bulletObj->AddComponent<dae::TextureRenderer>("Galaga.png");
	bulletObj->AddComponent<Bullet>(GetOwner()->GetTransform()->GetLocalPosition());

	++m_activeBullets;
	m_currentCooldown += m_shootCooldown;

	//Add to scene
	SceneManager::GetInstance().GetCurrentScene()->Add(std::move(bulletObj));
}

bool dae::PlayerShip::CanShoot() const
{
	return m_activeBullets < m_maxActiveBullets && m_currentCooldown <= 0.f;
}
