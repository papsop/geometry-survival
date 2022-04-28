#pragma once
#include <math.h>
#include "../../Utils/VectorUtils.h"
#include "../../Debug/Logger.h"
namespace Engine
{
    struct Transform
    {
        math::Vec2 Position;
        float Rotation;
        math::Vec2 Scale;

        Transform() : Position(math::Vec2(0.0f, 0.0f)), Rotation(0.0f), Scale(math::Vec2(1.0f, 1.0f)) {}

        void SetPosition(math::Vec2 pos) { Position = pos; }

        math::Vec2 Forward()
        {
            return { cosf(math::DEG_TO_RAD(Rotation)), -sinf(math::DEG_TO_RAD(Rotation)) };
        }

        bool operator==(const Transform& rhs) const
        {
            return (rhs.Position == Position && rhs.Rotation == Rotation && rhs.Scale == Scale);
        }
        bool operator!=(const Transform& rhs) const
        {
            return !(*this == rhs);
        }
        Transform operator+(Transform const& rhs)
        {
            this->Position += rhs.Position;
            this->Rotation += rhs.Rotation;
            this->Scale    += rhs.Scale;
            return *this;
        }
    };
};