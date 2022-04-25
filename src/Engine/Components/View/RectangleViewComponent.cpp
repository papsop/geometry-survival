#include "RectangleViewComponent.h"
#include "../../Managers/SubsystemManager.h"

namespace Engine
{


	RectangleViewComponent::RectangleViewComponent(GameObject& obj, int zIndex, const RectangleViewDef& def)
		: IRenderableShapeComponent(obj, view::RENDERABLE_TYPE::RECTANGLE, zIndex)
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
		SubsystemManager::Get().GetViewSubsystem().RegisterComponent(this);
		// update shape's transform
		if (m_useAbsoluteTransform)
			m_renderableTransform = m_localTransform;
		else
			m_renderableTransform = Owner.GetTransform() + m_localTransform;
	}

	RectangleViewComponent::~RectangleViewComponent()
	{
		SubsystemManager::Get().GetViewSubsystem().UnregisterComponent(this);
	}

	void RectangleViewComponent::Update(float dt)
	{
		// update shape's transform
		if (m_useAbsoluteTransform)
			m_renderableTransform = m_localTransform;
		else
			m_renderableTransform = Owner.GetTransform() + m_localTransform;
	}

	void RectangleViewComponent::OnCollision(GameObject& other)
	{
	}

};