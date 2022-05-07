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

		template<typename T>
        void RegisterComponentType();

		template<typename T>
        void RegisterComponent(T* component);

		template<typename T>
		void UnregisterComponent(T* component);

        void Update(float dt);

        template<typename T>
        std::vector<T*> GetComponentsContainer();
    private:
        std::map<uint32_t, std::unique_ptr<ComponentsContainer> > m_containers;
    };
}

#include "ComponentManager.inl"