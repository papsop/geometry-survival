#pragma once
#include "../GameObject.h"

namespace Game
{
    class IGameObjectFactory
    {
    public:
        IGameObjectFactory() = default;
        virtual ~IGameObjectFactory() = default;

        virtual std::shared_ptr<GameObject> CreateGameObject() const = 0;
    };

    class PlayerFactory : public IGameObjectFactory
    {
    public:
        ~PlayerFactory() override = default;

        std::shared_ptr<GameObject> CreateGameObject() const override;
    };
};