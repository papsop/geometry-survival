#pragma once
#include "../../Debug/Logger.h"
#include "../../Components/Core.h"
#include "../../Components/Physics.h"
#include "../../Components/View.h"
#include "../../Utils/IdGenerator.h"
#include "GameObjectTag.h"

#include <unordered_map>
#include <map>
#include <queue>
#include <memory>
#include <assert.h>
#include <type_traits>

namespace Engine
{
    using GameObjectID = uint32_t;

    class Scene;
    struct CollisionData;

    class GameObject
    {
    public:
		// better name?
		using FuncOverComponents = std::function<void(IComponent*)>;
        // Components Management
        template<typename T,
                typename = enable_if_base_of_component<T>
                >
        bool HasComponent() const;

        template<typename T, 
                typename ... Args,
                typename = enable_if_base_of_component<T>
                >
        void AddComponent(Args&& ... args);

        template<typename T,
                typename = enable_if_base_of_component<T>
                >
        void RemoveComponent();

        template<typename T,
                typename = enable_if_base_of_component<T>
                >
        T* GetComponent();

        // --------------------------
        GameObject(uint32_t id, const char* debugName = "unnamed", GameObjectTag tag = GameObjectTag::UNTAGGED, ITransform::PositionSpace space = ITransform::PositionSpace::WorldSpace);

        ~GameObject() = default;

        const GameObjectID ID;
        const GameObjectTag Tag;
        const char* DebugName;

        ITransform* GetTransform() { return m_transform.get(); }

        void OnCollisionStart(CollisionData& collision);
        void OnCollisionEnd(CollisionData& collision);

        void Destroy();
        void SetActive(bool a);

        bool ShouldDestroy() const { return m_shouldDestroy; }
        bool IsActive() const { return m_isActive; }
        bool ShouldUpdate() const { return m_isActive && !m_shouldDestroy; }

        void SetScene(Scene* scene) { m_scene = scene; }
        Scene& GetScene() { return *m_scene; }

        void SendMessageTo(GameObject* receiver, MessageType type);
        void ReceiveMessage(const Message& message);

        void ForEachComponent(FuncOverComponents func);

    private:
        std::unordered_map<uint32_t, std::unique_ptr<IComponent>> m_components = {};
        bool m_shouldDestroy = false;
        bool m_isActive = false;

        std::unique_ptr<ITransform> m_transform;
        Scene* m_scene;

        friend class GameObjectManager;
    };
};

#include "GameObject.inl"