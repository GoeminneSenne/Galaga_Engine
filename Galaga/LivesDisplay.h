#pragma once
#include <Component.h>
#include <IObserver.h>

#include <SDL3/SDL_rect.h>

namespace dae
{
	class TextComponent;
	class Lives;

	class LivesDisplay final: public Component, public IObserver
	{
	public:
		explicit LivesDisplay(GameObject* pOwner, Lives* pLives = nullptr);

		void Notify(EventId eventId, GameObject* object) override;
		void Render() const override;

	private:
		int m_numLives{};

		std::shared_ptr<Texture2D> m_texture{};
		constexpr static SDL_FRect m_srcRect{ 109.f, 1.f, 16.f, 16.f };
		constexpr static float m_size{ 32.f };
		
	};
}