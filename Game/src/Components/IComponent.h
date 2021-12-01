#pragma once

namespace Game
{
    class IComponent
    {
    public:
        IComponent() = default;
        virtual ~IComponent() = default;

        virtual void Update(float dt) = 0;
    };
};