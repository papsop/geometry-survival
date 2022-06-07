#pragma once

namespace Engine
{

    class Scene;

    class IState
    {
    public:
        IState() = default;
        ~IState() = default;

        virtual void OnInit() {};
        virtual void OnDestroy() {};

        virtual void Update(float dt) = 0;
    };
}
