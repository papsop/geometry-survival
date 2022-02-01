#pragma once
#include "../Subsystems/ViewSubsystem.h"
#include "../Subsystems/PhysicsSubsystem.h"
#include "../Subsystems/ComponentSubsystem.h"

#include <map>
#include <memory>

namespace Engine
{
    class Application;
    class SubsystemManager
    {

    public:
        ~SubsystemManager() = default;

        static SubsystemManager& Get();

        template<typename T>
        void RegisterComponentType()
        {
            auto ID = ComponentSubsystem::GetSubsystemID<T>();
            LOG_DEBUG("Registered component type '%s'", typeid(T).name());
            m_subsystems.emplace_back(std::make_unique<ComponentSubsystem>());
        }

        template<typename T>
        void RegisterComponent(T* component)
        {
            auto ID = ComponentSubsystem::GetSubsystemID<T>();
            DD_ASSERT(ID < m_subsystems.size(), "ComponentSubsystem for this component isn't registered");
            LOG_DEBUG("Registered component '%s'", typeid(T).name());
            m_subsystems[ID]->RegisterComponent(component);
        }

        template<typename T>
        void UnregisterComponent(T* component)
        {
            auto ID = ComponentSubsystem::GetSubsystemID<T>();
            DD_ASSERT(ID < m_subsystems.size(), "ComponentSubsystem for this component isn't registered");
            LOG_DEBUG("Unregistered component '%s'", typeid(T).name());
            m_subsystems[ID]->UnregisterComponent(component);
        }

        void Update(float dt);

        ViewSubsystem& GetViewSubsystem() { return *m_view; }
        PhysicsSubsystem& GetPhysicsSubsystem() { return *m_physics; }

        ViewSubsystem* GetViewSubsystemPointer() { return m_view.get(); }
    private:
        SubsystemManager();

        std::vector<std::unique_ptr<ComponentSubsystem>> m_subsystems;
        std::unique_ptr<ViewSubsystem> m_view;
        std::unique_ptr<PhysicsSubsystem> m_physics;

    friend class Application; // only Application can create a manager
    };
};