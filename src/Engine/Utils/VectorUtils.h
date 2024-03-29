#pragma once
#include <cmath>
#include <SFML/System/Vector2.hpp>
#include <box2d/b2_math.h>
#include <random>

namespace Engine
{
    namespace math
    {
        const float M_PI_F = 3.14159274101257324219f;

        using Vec2 = b2Vec2;

        float RAD_TO_DEG(float angle);

        float DEG_TO_RAD(float angle);

        Vec2 GetVectorFromAngle(float angleRad);
				float AngleBetweenVecs(Vec2 a, Vec2 b);
				float AngleOfVec(Vec2 a);

        float V2fLengthSquared(const Vec2& v);
        float V2FDistanceSquared(const Vec2& a, const Vec2& b);
        float V2fLength(const Vec2& v);

        Vec2 V2fNormalize(const Vec2& v);

        float V2fDot(const Vec2& v1, const Vec2& v2);

        float V2fCross(const Vec2& v1, const Vec2& v2);
        float V2fCross(const Vec2& v1, const Vec2& v2);

        float RandomFloatBetween(float min, float max);
    };
};