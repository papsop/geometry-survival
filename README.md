# Dungeons & Geometry

![image](https://user-images.githubusercontent.com/9076709/155303636-18c13151-962f-4707-a7a1-2107b92c55e2.png)

TODO by priority: 
- YAML support for saving a scene
	- Serializing/seserializing GameObjects (mainly components)
- Runtime `IComponent::Requires<>()` checking (in case required component gets deleted during gameplay)
- Local level event listening
	- Currently there's only a global one (IEventDispatcher<> and IEventListener<>)
- Multiple views in one scene
	- And the camera system in general