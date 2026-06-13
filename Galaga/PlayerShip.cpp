#include "PlayerShip.h"

#include <algorithm>
#include <memory>
#include <Event.h>
#include <EventQueue.h>

#include "Bullet.h"
#include "Collider.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "TextureRenderer.h"


dae::PlayerShip::PlayerShip(GameObject* pOwner, float leftBounds, float rightBounds)
	: Component(pOwner), m_leftBounds(leftBounds), m_rightBounds(rightBounds)
{
	auto texture = GetOwner()->GetComponent<TextureRenderer>();
	texture->SetSourceRect(m_srcRect);
	texture->SetDestinationSize(m_width, m_height);

	EventQueue::GetInstance().Subscribe(this);
}

dae::PlayerShip::~PlayerShip()
{
	EventQueue::GetInstance().Unsubscribe(this);

	InputManager::GetInstance().RemoveKeybind(SDL_SCANCODE_D, KeyState::Pressed);
	InputManager::GetInstance().RemoveKeybind(SDL_SCANCODE_A, KeyState::Pressed);
	InputManager::GetInstance().RemoveKeybind(SDL_SCANCODE_W, KeyState::Pressed);
	InputManager::GetInstance().RemoveKeybind(SDL_SCANCODE_SPACE, KeyState::Down);
}

void dae::PlayerShip::Update(float deltaTime)
{
	if (m_currentCooldown > 0.f)
	{
		m_currentCooldown -= deltaTime;
	}

	//Level bounds
	auto pos = GetOwner()->GetTransform()->GetLocalPosition();
	pos.x = std::clamp(pos.x, m_leftBounds, m_rightBounds - m_width);
	GetOwner()->GetTransform()->SetLocalPosition(pos);
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
	bulletObj->AddComponent<Collider>(32.f, 32.f);

	++m_activeBullets;
	m_currentCooldown += m_shootCooldown;

	//Add to scene
	SceneManager::GetInstance().GetCurrentScene()->Add(std::move(bulletObj));
}

bool dae::PlayerShip::CanShoot() const
{
	return m_activeBullets < m_maxActiveBullets && m_currentCooldown <= 0.f;
}
