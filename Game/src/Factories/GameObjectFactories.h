#pragma once
#include "../Core/GameObject.h"

namespace Game
{
    class IGameObjectFactory
    {
    public:
        IGameObjectFactory() = default;
        virtual ~IGameObjectFactory() = default;

        virtual uint32_t CreateGameObject() const = 0;
    };

    class DebugGOFactory : public IGameObjectFactory
    {
    public:
        ~DebugGOFactory() override = default;
        uint32_t CreateGameObject() const override;
    private:
    };

    class PlayerFactory : public IGameObjectFactory
    {
    public:
        ~PlayerFactory() override = default;

        uint32_t CreateGameObject() const override;
    };

    class SeekingEnemyFactory : public IGameObjectFactory
    {
    public:
        ~SeekingEnemyFactory() override = default;
        uint32_t CreateGameObject() const override;
    private:
    };
};