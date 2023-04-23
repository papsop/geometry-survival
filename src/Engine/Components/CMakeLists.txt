set(SOURCES
	Core.h
	Physics.h
	View.h
	UI.h

	Core/Transform_old.h
	Core/ITransform.h
	Core/ITransform.cpp
	Core/RectTransform.h
	Core/RectTransform.inl
	Core/RectTransform.cpp
	Core/Transform.h
	Core/Transform.cpp
	Core/IComponent.h
	Core/IComponent.cpp
	Core/IComponent.inl
	Core/IConstraint.h
	Core/IConstraint.cpp

	Physics/PhysicsBodyComponent.h
	Physics/PhysicsBodyComponent.cpp
	Physics/CircleFixtureComponent.h
	Physics/CircleFixtureComponent.cpp
	Physics/RectangleFixtureComponent.h
	Physics/RectangleFixtureComponent.cpp
	Physics/TriangleFixtureComponent.h
	Physics/TriangleFixtureComponent.cpp

	View/ShapeViewComponent.h
	View/ShapeViewComponent.cpp
	View/RectangleViewComponent.h
	View/RectangleViewComponent.cpp
	View/TextViewComponent.h
	View/TextViewComponent.cpp

	Drawables/ShapeDrawableComponent.h
	Drawables/ShapeDrawableComponent.cpp
	Drawables/SpriteDrawableComponent.h
	Drawables/SpriteDrawableComponent.cpp

	UI/LayoutElementComponent.h
	UI/LayoutElementComponent.cpp
	UI/HorizontalLayoutComponent.h
	UI/HorizontalLayoutComponent.cpp
	UI/VerticalLayoutComponent.h
	UI/VerticalLayoutComponent.cpp
)

target_sources(${ENGINE_PROJECT} PUBLIC 
	${SOURCES}
)
