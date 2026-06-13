#pragma once
#include "Component.h"

namespace galaga
{
	class BackgroundComponent final : public dae::Component
	{
	public:
		explicit BackgroundComponent(dae::GameObject* pOwner, float scrollSpeed, float height);
		~BackgroundComponent() override = default;
		BackgroundComponent(const BackgroundComponent&) = delete;
		BackgroundComponent(BackgroundComponent&&) = delete;
		BackgroundComponent& operator=(const BackgroundComponent&) = delete;
		BackgroundComponent& operator=(BackgroundComponent&&) = delete;

		void Update(float deltaTime) override;

	private:
		float m_scrollSpeed{};
		float m_height{};
	};
}
