#pragma once
#include <math.h>
#include <SFML/System/Vector2.hpp>

namespace Game
{
    namespace math
    {
        const float M_PI_F = 3.14159274101257324219f;

        typedef sf::Vector2f Vec2;

        float RAD_TO_DEG(float angle);

        float DEG_TO_RAD(float angle);

        float V2fLengthSquared(const Vec2& v);

        float V2fLength(const Vec2& v);

        Vec2 V2fNormalize(const Vec2& v);

        float V2fDot(const Vec2& v1, const Vec2& v2);

        float V2fCross(const Vec2& v1, const Vec2& v2);
    };
};