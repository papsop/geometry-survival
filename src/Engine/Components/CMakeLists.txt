set(SOURCES
	Core.h
	Physics.h

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

	Drawables/ShapeDrawableComponent.h
	Drawables/ShapeDrawableComponent.cpp
	Drawables/SpriteDrawableComponent.h
	Drawables/SpriteDrawableComponent.inl
	Drawables/SpriteDrawableComponent.cpp
	Drawables/TextDrawableComponent.h
	Drawables/TextDrawableComponent.cpp	
	Drawables/AnimationControllerComponent.h
	Drawables/AnimationControllerComponent.cpp
	Drawables/AnimationStateMachine.h
	Drawables/AnimationStateMachine.inl
	Drawables/AnimationStateMachine.cpp

	Animations/AnimationData.h
	Animations/IAnimationPlayRequester.h
	Animations/AnimatorController.h
	Animations/AnimatorController.inl
	Animations/AnimatorController.cpp
	Animations/AnimatorComponent.h
	Animations/AnimatorComponent.cpp
)

target_sources(${ENGINE_PROJECT} PUBLIC 
	${SOURCES}
)
