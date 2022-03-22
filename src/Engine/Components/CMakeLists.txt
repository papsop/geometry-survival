set(SOURCES
	Core.h
	Physics.h
	View.h

	Core/Transform.h
	Core/IComponent.h
	Core/IComponent.cpp

	Physics/RigidbodyComponent.h
	Physics/RigidbodyComponent.cpp
	Physics/CircleColliderComponent.h
	Physics/CircleColliderComponent.cpp

	View/TriangleComponent.h
	View/TriangleComponent.cpp
)

target_sources(${ENGINE_PROJECT} PUBLIC 
	${SOURCES}
)
