#pragma once
#include "../View/Renderables.h"
#include "../Core/CameraData.h"
#include "../Components/Core/ITransform.h"

namespace Engine
{
    class Application;
    class ViewManager;

    namespace view
    {
        class IViewStrategy
        {
		public:
            IViewStrategy(ViewManager& viewManager)
                : m_viewManager(viewManager) 
                {};

            virtual ~IViewStrategy() = default;

            virtual void PollEvents() = 0;
            virtual void PreRender() = 0;
			virtual void RenderRenderable(Renderable& renderable) = 0;
            virtual void PostRender() = 0;

            virtual void DebugRenderLine(ITransform::PositionSpace space, math::Vec2 a, math::Vec2 b, sf::Color color)  {};
            virtual void DebugRenderCircle(ITransform::PositionSpace space, math::Vec2 center, float radius, sf::Color color) {};
            virtual void DebugRenderRectangle(ITransform::PositionSpace space, math::Vec2 center, math::Vec2 size, float angle, sf::Color color, sf::Color fillColor) {};
            virtual void DebugRenderText(ITransform::PositionSpace space, std::string text, math::Vec2 position, float size, sf::Color color) {};

            virtual void SetView(const CameraData& cameraData) = 0;
            virtual sf::Vector2f GetMousePosition() = 0;
        protected:
            ViewManager& m_viewManager;
        };
    }
}