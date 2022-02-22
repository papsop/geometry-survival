#pragma once

namespace Engine
{

    class Scene;

    class IState
    {
    public:
        IState() = default;
        ~IState() = default;

        virtual void Enter() = 0;
        virtual void Update(float dt) = 0;
        virtual void Exit() = 0;
    };

    class ISceneState : public IScene
    {
    public:
        ISceneState(Scene* scene)
            : m_scene(scene) {};
        ~ISceneState() = default;

        virtual void Enter() = 0;
        virtual void Update(float dt) = 0;
        virtual void Exit() = 0;
    protected:
        Scene* m_scene;
    };
}
