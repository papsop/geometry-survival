#include "ShapeViewComponent.h"
#include "../../Managers/SubsystemManager.h"

namespace Engine
{

	ShapeViewComponent::ShapeViewComponent(GameObject& obj, int zIndex, const ShapeViewDef& def)
		: IRenderableShapeComponent(obj, zIndex)
		, m_shape(m_shapeTransform)
	{
		m_useAbsoluteTransform = def.UseAbsoluteTransform;

		m_localTransform.Position = def.Position;
		m_localTransform.Rotation = def.Rotation;
		m_localTransform.Scale    = { 0.0f, 0.0f }; // use owner's

		m_shape.Color = def.Color;
		m_shape.PointCount = def.PointCount;
		m_shape.Radius = def.Radius;

		// update shape's transform
		if (m_useAbsoluteTransform)
			m_shapeTransform = m_localTransform;
		else
			m_shapeTransform = Owner.GetTransform() + m_localTransform;
	}

	void ShapeViewComponent::OnCreate()
	{
		SubsystemManager::Get().GetViewSubsystem().RegisterComponent(this);
	}

	ShapeViewComponent::~ShapeViewComponent()
	{
		SubsystemManager::Get().GetViewSubsystem().UnregisterComponent(this);
	}

	void ShapeViewComponent::Update(float dt)
	{
		// update shape's transform
		if (m_useAbsoluteTransform)
			m_shapeTransform = m_localTransform;
		else
			m_shapeTransform = Owner.GetTransform() + m_localTransform;
	}

}

