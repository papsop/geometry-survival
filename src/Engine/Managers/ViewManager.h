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

	struct ResolutionEntry
	{
		const char* Name;
		math::Vec2 Value;
		ResolutionEntry(const char* name, math::Vec2 val) : Name(name), Value(val) {}
		ResolutionEntry() = default;
	};

	struct ViewManagerSettings
	{
		ResolutionEntry ResolutionEntry;
		bool Fullscreen;
	};

	class CameraComponent;

	class ViewManager : public IManager, public IEventListener<event::E_OnShowDebugKeyAction>
	{
	public:

		~ViewManager() = default;
		static ViewManager& Get();

		void RegisterComponent(IRenderableComponent* component);
		void RegisterComponent(IDrawableComponent* component);
		//void RegisterComponent(IUIComponent* component);
		void RegisterComponent(IImGuiComponent* component);
		void RegisterComponent(IDebuggable* component);

		void UnregisterComponent(IRenderableComponent* component);
		void UnregisterComponent(IDrawableComponent* component);
		//void UnregisterComponent(IUIComponent* component);
		void UnregisterComponent(IImGuiComponent* component);
		void UnregisterComponent(IDebuggable* component);

		// Application's interface to ViewStrategy
		void PollEvents();
		sf::Vector2f GetMousePosition();

		sf::Vector2f coordsToPixels(b2Vec2 coords);
		b2Vec2       pixelsToCoords(sf::Vector2f pixels);
		float        coordToPixel(float coord);
		float        pixelToCoord(float pixel);

    sf::Vector2i MapCoordsToPixel(sf::Vector2f coords);
    sf::Vector2f MapPixelToCoords(sf::Vector2i pixel);

		void Update(float dt);
		void SetViewStrategy(view::IViewStrategy* viewStrategy);
		view::IViewStrategy* GetViewStrategy() { return m_viewStrategy.get(); };

		int GetZIndexFromPool() { return 0; }
		bool IsDebugDrawing() { return m_shouldDrawDebug; }

		math::Vec2 GetResolution() { return m_viewStrategy->GetResolution(); };
		
		void SetSettings(const ViewManagerSettings& def);
		ViewManagerSettings GetSettings();

  protected:
    void ReceiveEvent(const event::E_OnShowDebugKeyAction& eventData) override;

	private:
		int m_pixelsPerMeter; // config?
		bool m_isViewdirty = false;
		ViewManager();
		
		void VirtualOnInit() override;
		void VirtualOnDestroy() override;
		void DebugDraw(float dt);

		std::unique_ptr<view::IViewStrategy> m_viewStrategy;
		std::multimap< view::Layer, IRenderableComponent*> m_renderableComponents;
		//std::vector< IUIComponent* > m_uiComponents;
		std::vector< IImGuiComponent* > m_imguiComponents;
		std::vector< IDrawableComponent* > m_drawableComponents;
		std::vector< IDebuggable* > m_debugs;

		bool m_shouldDrawDebug = false;

		friend class Application;
		friend class CameraComponent;

	};
};
