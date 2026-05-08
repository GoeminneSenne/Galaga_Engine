#include "PlayerShip.h"

#include <memory>
#include <Event.h>
#include <EventQueue.h>

#include "Bullet.h"
#include "SceneManager.h"
#include "TextureRenderer.h"


dae::PlayerShip::PlayerShip(GameObject* pOwner)
	: Component(pOwner)
{
	auto texture = GetOwner()->GetComponent<TextureRenderer>();
	texture->SetSourceRect(m_srcRect);
	texture->SetDestinationSize(m_width, m_height);
}

void dae::PlayerShip::ShootBullet()
{
	//constexpr SDL_FRect bulletSrc{ 307.f, 154.f, 16.f, 16.f };

	std::unique_ptr<EventArgs> args = std::make_unique<PlaySFXArgs>("./Data/PlayerShoot.mp3");
	EventQueue::GetInstance().SendEvent(make_sdbm_hash("PlaySFX"), std::move(args));
	
	auto bulletObj = std::make_unique<dae::GameObject>();
	bulletObj->AddComponent<dae::TextureRenderer>("Galaga.png");
	//texture->SetSourceRect(bulletSrc);
	//texture->SetDestinationSize(bulletSrc.w, bulletSrc.h);

	bulletObj->AddComponent<Bullet>(GetOwner()->GetTransform()->GetLocalPosition());

	SceneManager::GetInstance().GetCurrentScene()->Add(std::move(bulletObj));
}
