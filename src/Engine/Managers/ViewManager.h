#pragma once
#include "IManager.h"
#include "../Components/View.h"
#include "../View/IViewStrategy.h"
#include "../Debug/IDebuggable.h"

#include <vector>
#include <set>
#include <memory>

namespace Engine
{
	class CameraComponent;
	class ViewManager : public IManager
	{
	public:
		~ViewManager() = default;
		static ViewManager& Get();

		void RegisterComponent(IRenderableShapeComponent* component);
		void RegisterComponent(IRenderableTextComponent* component);
		void RegisterComponent(IDebuggable* component);
		void RegisterComponent(CameraComponent* component);

		void UnregisterComponent(IRenderableShapeComponent* component);
		void UnregisterComponent(IRenderableTextComponent* component);
		void UnregisterComponent(IDebuggable* component);
		void UnregisterComponent(CameraComponent* component);

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

		int GetZIndexFromPool() { return m_zIndexPool++; }
		bool IsDebugDrawing() { return m_shouldDrawDebug; }
	private:
		const int PIXELS_PER_METER = 10; // config?
		static bool compareZIndex(const IRenderableShapeComponent* s1, const IRenderableShapeComponent* s2)
		{
			return s1->ZIndex < s2->ZIndex;
		}

		int m_zIndexPool = 1000;

		ViewManager();

		void VirtualOnDestroy() override;

		std::unique_ptr<view::IViewStrategy> m_viewStrategy;
		std::set< IRenderableShapeComponent*, decltype(&compareZIndex)> m_shapes;
		std::vector< IRenderableTextComponent* > m_texts;
		std::vector< IDebuggable* > m_debugs;
		std::vector< CameraComponent* > m_cameras;

		bool m_shouldDrawDebug = false;

		friend class Application;
		friend class CameraComponent;
	};
};
