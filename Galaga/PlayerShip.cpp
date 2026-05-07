#include "PlayerShip.h"

#include <memory>
#include <Event.h>
#include <EventQueue.h>

#include "SceneManager.h"
#include "TextureRenderer.h"


dae::PlayerShip::PlayerShip(GameObject* pOwner)
	: Component(pOwner)
{
}

void dae::PlayerShip::ShootBullet()
{
	std::unique_ptr<EventArgs> args = std::make_unique<PlaySFXArgs>("./Data/PlayerShoot.mp3");
	EventQueue::GetInstance().SendEvent(make_sdbm_hash("PlaySFX"), std::move(args));
	
	auto bulletObj = std::make_unique<dae::GameObject>();
	bulletObj->GetTransform()->SetLocalPosition(GetOwner()->GetTransform()->GetWorldPosition());
	bulletObj->AddComponent<dae::TextureRenderer>("Galaga/ship2.png");

	SceneManager::GetInstance().GetCurrentScene()->Add(std::move(bulletObj));
}
