set(SOURCES
	Core.h
	Physics.h
	View.h

	Core/Transform.h
	Core/IComponent.h
	Core/IComponent.cpp

	Physics/PhysicsBodyComponent.h
	Physics/PhysicsBodyComponent.cpp
	Physics/CircleFixtureComponent.h
	Physics/CircleFixtureComponent.cpp
	Physics/RectangleFixtureComponent.h
	Physics/RectangleFixtureComponent.cpp

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
