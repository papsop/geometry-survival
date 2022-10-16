#pragma once
#include "IManager.h"
#include "../Components/View.h"
#include "../View/IViewStrategy.h"
#include "../Debug/IDebuggable.h"
#include "ViewLayers.h"
#include "../Utils/VectorUtils.h"
#include "../Core/Events.h"
#include "../Core/EventData.h"

#include <vector>
#include <map>
#include <memory>

namespace Engine
{
	class CameraComponent;
	class ViewManager : public IManager, public IEventListener<event::E_OnShowDebugKeyAction>
	{
	public:
		~ViewManager() = default;
		static ViewManager& Get();

		void RegisterComponent(IRenderableComponent* component);
		void RegisterComponent(IDebuggable* component);

		void UnregisterComponent(IRenderableComponent* component);
		void UnregisterComponent(IDebuggable* component);

		// Application's interface to ViewStrategy
		void PollEvents();
		sf::Vector2f GetMousePosition();


		sf::Vector2f coordsToPixels(b2Vec2 coords);
		b2Vec2       pixelsToCoords(sf::Vector2f pixels);
		float        coordToPixel(float coord);
		float        pixelToCoord(float pixel);

		void Update(float dt);
		void SetViewStrategy(view::IViewStrategy* viewStrategy);
		view::IViewStrategy* GetViewStrategy() { return m_viewStrategy.get(); };

		int GetZIndexFromPool() { return 0; }
		bool IsDebugDrawing() { return m_shouldDrawDebug; }

		math::Vec2 GetResolution() { return m_viewStrategy->GetResolution(); };

  protected:
    void ReceiveEvent(const event::E_OnShowDebugKeyAction& eventData) override;

	private:
		int m_pixelsPerMeter; // config?

		ViewManager();
		
		void VirtualOnInit() override;
		void VirtualOnDestroy() override;

		std::unique_ptr<view::IViewStrategy> m_viewStrategy;
		std::multimap< view::Layer, IRenderableComponent*> m_renderableComponents;
		std::vector< IDebuggable* > m_debugs;

		bool m_shouldDrawDebug = false;

		friend class Application;
		friend class CameraComponent;

	};
};
