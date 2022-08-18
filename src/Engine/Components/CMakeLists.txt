set(SOURCES
	Core.h
	Physics.h
	View.h

	Core/Transform.h
	Core/ITransform.h
	Core/ScreenTransform.h
	Core/ScreenTransform.cpp
	Core/WorldTransform.h
	Core/WorldTransform.cpp
	Core/IComponent.h
	Core/IComponent.cpp
	Core/IComponent.inl

	Physics/PhysicsBodyComponent.h
	Physics/PhysicsBodyComponent.cpp
	Physics/CircleFixtureComponent.h
	Physics/CircleFixtureComponent.cpp
	Physics/RectangleFixtureComponent.h
	Physics/RectangleFixtureComponent.cpp
	Physics/TriangleFixtureComponent.h
	Physics/TriangleFixtureComponent.cpp

	View/CameraComponent.h
	View/CameraComponent.cpp

	View/ShapeViewComponent.h
	View/ShapeViewComponent.cpp
	View/RectangleViewComponent.h
	View/RectangleViewComponent.cpp
)

target_sources(${ENGINE_PROJECT} PUBLIC 
	${SOURCES}
)
