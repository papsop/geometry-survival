#pragma once
#include "IManager.h"
#include "../Components/Core.h"

#include <map>
#include <memory>

namespace Engine
{
	class ComponentsContainer
	{
	public:
		typedef std::function<void(IComponent*)> TComponentEnumerate;

		ComponentsContainer(uint32_t ID) : ContainerID(ID) {};
		void RegisterComponent(IComponent* component);
		void UnregisterComponent(IComponent* component);

		void IterateOverComponents(TComponentEnumerate func);
		void Update(float dt);
		void FixedUpdate(float dt);

		const uint32_t ContainerID;

	private:
		std::vector< IComponent* > m_components;
	};

	class ComponentManager : public IManager
	{
	public:
		static ComponentManager& Get();
		ComponentManager() = default;
		~ComponentManager() = default;

		template<typename T,
			typename = enable_if_base_of_component<T>
		>
		void RegisterComponentType();

		template<typename T,
			typename = enable_if_base_of_component<T>
		>
		void RegisterComponent(T* component);

		template<typename T,
			typename = enable_if_base_of_component<T>
		>
		void UnregisterComponent(T* component);

		void Update(float dt) override;
		void FixedUpdate(float dt) override;

		template<typename T,
			typename = enable_if_base_of_component<T>
		>
		std::vector<T*> GetComponentsContainer();
	private:
		std::map<uint32_t, std::unique_ptr<ComponentsContainer> > m_containers;
	};
}

#include "ComponentManager.inl"