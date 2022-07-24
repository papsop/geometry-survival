#include "ShapeViewComponent.h"
#include "../../Managers/ComponentManager.h"

namespace Engine
{

	ShapeViewComponent::ShapeViewComponent(GameObject& obj, const ShapeViewDef& def)
		: IRenderableShapeComponent(obj, view::Renderable_Type::SHAPE, def.Layer)
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
		ViewManager::Get().RegisterComponent(this);
		// update shape's transform
		if (m_useAbsoluteTransform)
			m_renderableTransform = m_localTransform;
		else
			m_renderableTransform = Owner.GetTransform() + m_localTransform;
	}

	ShapeViewComponent::~ShapeViewComponent()
	{
		ViewManager::Get().UnregisterComponent(this);
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

