#include "ShapeViewComponent.h"
#include "../../Managers/SubsystemManager.h"

namespace Engine
{

	ShapeViewComponent::ShapeViewComponent(GameObject& obj, int zIndex, const ShapeViewDef& def)
		: IRenderableShapeComponent(obj, view::RENDERABLE_TYPE::SHAPE, zIndex)
	{
		m_useAbsoluteTransform = def.UseAbsoluteTransform;

		m_localTransform.Position		= def.Position;
		m_localTransform.Rotation		= def.Rotation;
		m_localTransform.Scale			= { 0.0f, 0.0f }; // use owner's

		m_renderable.shape.Color		= def.Color;
		m_renderable.shape.PointCount	= def.PointCount;
		m_renderable.shape.Radius		= def.Radius;
	}

	void ShapeViewComponent::OnCreate()
	{
		SubsystemManager::Get().GetViewSubsystem().RegisterComponent(this);
		// update shape's transform
		if (m_useAbsoluteTransform)
			m_renderableTransform = m_localTransform;
		else
			m_renderableTransform = Owner.GetTransform() + m_localTransform;
	}

	ShapeViewComponent::~ShapeViewComponent()
	{
		SubsystemManager::Get().GetViewSubsystem().UnregisterComponent(this);
	}

	void ShapeViewComponent::Update(float dt)
	{
		// update shape's transform
		if (m_useAbsoluteTransform)
			m_renderableTransform = m_localTransform;
		else
			m_renderableTransform = Owner.GetTransform() + m_localTransform;
	}

}
