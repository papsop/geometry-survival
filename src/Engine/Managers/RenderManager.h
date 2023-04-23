#pragma once
#include "IManager.h"
#include "../Components/Core/IComponent.h"
#include "../Core/Events.h"
#include "../Core/EventData.h"

#include "../Debug/IDebuggable.h"

#include <SFML/Graphics/Drawable.hpp>
#include <vector>

namespace Engine
{
	class Application;

	class RenderManager : public IManager, public IEventListener<event::E_OnShowDebugKeyAction>
	{
		friend class Application;

	public:
		static RenderManager& Get();

		~RenderManager() = default;

		void Update(float dt) override;
		void Render(float dt);

		void RegisterComponent(IDrawableComponent* component);
		void UnregisterComponent(IDrawableComponent* component);

		inline float coordToPixel(float coord) { return coord * m_pixelsPerMeter; };
		inline float pixelToCoord(float pixel) { return pixel / m_pixelsPerMeter; };
		inline sf::Vector2f coordsToPixels(b2Vec2 coords) { return { coords.x * m_pixelsPerMeter, -coords.y * m_pixelsPerMeter }; };
		inline b2Vec2 pixelsToCoords(sf::Vector2f pixels) { return { pixels.x / m_pixelsPerMeter, -pixels.y / m_pixelsPerMeter }; };
		inline float Box2DRotationToSFML(float angle) { return 360.0f - math::RAD_TO_DEG(angle); }

		void SetView(CameraData cameraData);
	protected:
		void VirtualOnInit() override;
		void VirtualOnDestroy() override;

		void ReceiveEvent(const event::E_OnShowDebugKeyAction& eventData) override;

	private:
		bool m_shouldUpdateDebugs = false;
		float m_pixelsPerMeter = 10;
		std::unique_ptr<sf::RenderWindow> m_window;
		std::vector<IDrawableComponent*> m_drawableComponents;

		RenderManager() = default;

		void ReloadView();
		void ApplyTransformToDrawable(const ITransform::AbsoluteTransform transform, sf::Drawable* drawable);
	};
}
