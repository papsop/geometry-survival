#include "RectangleViewComponent.h"

namespace Engine
{


	RectangleViewComponent::RectangleViewComponent(GameObject& obj, int zIndex, const RectangleViewDef& def)
		: IRenderableShapeComponent(obj, Engine::view::Renderable_Type::SHAPE, Engine::view::Layer::BACKGROUND)
	{
		m_useAbsoluteTransform				= def.UseAbsoluteTransform;

		m_localTransform.Position			= def.Position;
		m_localTransform.Rotation			= def.Rotation;
		m_localTransform.Scale				= { 0.0f, 0.0f }; // use owner's

		m_renderable.rectangle.FillColor	= def.Color;
		m_renderable.rectangle.Size			= def.Size;
	}

	void RectangleViewComponent::OnCreate()
	{
		ViewManager::Get().RegisterComponent(this);
		// update shape's transform
		if (m_useAbsoluteTransform)
			m_renderableTransform = m_localTransform;
		else
			m_renderableTransform = Owner.GetTransform() + m_localTransform;
	}

	RectangleViewComponent::~RectangleViewComponent()
	{
		ViewManager::Get().UnregisterComponent(this);
	}

	void RectangleViewComponent::Update(float dt)
	{
		// update shape's transform
		if (m_useAbsoluteTransform)
			m_renderableTransform = m_localTransform;
		else
			m_renderableTransform = Owner.GetTransform() + m_localTransform;
	}

};