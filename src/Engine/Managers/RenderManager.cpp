#include "RenderManager.h"
#include "../Application.h"

namespace Engine
{

	RenderManager& RenderManager::Get()
	{
		return Application::Instance().GetRenderManager();
	}

	void RenderManager::VirtualOnInit()
	{
		IEventListener<event::E_OnShowDebugKeyAction>::RegisterListener();
		ReloadView();
	}

	void RenderManager::VirtualOnDestroy()
	{
		IEventListener<event::E_OnShowDebugKeyAction>::UnregisterListener();
	}

	void RenderManager::RegisterComponent(IDrawableComponent* component)
	{
		m_drawableComponents.push_back(component);
	}

	void RenderManager::UnregisterComponent(IDrawableComponent* component)
	{
		m_drawableComponents.erase(std::remove(m_drawableComponents.begin(), m_drawableComponents.end(), component), m_drawableComponents.end());
	}

	void RenderManager::SetView(CameraData cameraData)
	{
		sf::View view;
		view.setCenter(coordsToPixels(cameraData.Center));
		view.setSize(1280, 720);
		view.setViewport({ .0f, .0f, 1.f, 1.f });
		m_window->setView(view);
	}

	void RenderManager::ReceiveEvent(const event::E_OnShowDebugKeyAction& eventData)
	{
		m_shouldUpdateDebugs = !m_shouldUpdateDebugs;
	}

	void RenderManager::ReloadView()
	{
		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;
		sf::VideoMode videoMode(1280, 720, 32);
		uint32 style = sf::Style::Titlebar | sf::Style::Close;

		m_window = std::make_unique<sf::RenderWindow>(videoMode, "test", style, settings);
		m_window->setJoystickThreshold(10);
	}

	void RenderManager::ApplyTransformToDrawable(const ITransform::AbsoluteTransform transform, sf::Drawable* drawable)
	{
		auto* transformableObject = dynamic_cast<sf::Transformable*>(drawable);
		if (!transformableObject)
			return;

		transformableObject->setPosition(coordsToPixels(transform.Position));
		transformableObject->setRotation(Box2DRotationToSFML(transform.Rotation));
		transformableObject->setScale({ 1.0f, 1.0f });
	}

	void RenderManager::Update(float dt)
	{
		
	}

	void RenderManager::Render(float dt)
	{
		IDrawableComponent::TDrawablesMap drawables;
		
		m_window->clear();

		// get all the drawables
		for (auto& drawableComponent : m_drawableComponents)
		{
			drawableComponent->GetDrawables(drawables);
		}


		// draw them
		for (auto& [layer, data] : drawables)
		{
			ApplyTransformToDrawable(data.first, data.second);

			m_window->draw(*data.second);
		}
		

		m_window->display();
	}

}