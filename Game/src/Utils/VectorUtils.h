#pragma once
#include <math.h>
#include <SFML/System/Vector2.hpp>

const float M_PI_F = 3.14159274101257324219f;


typedef sf::Vector2f Vec2;

constexpr float RAD_TO_DEG(float angle)
{
    return (angle * 180.0f) / M_PI_F;
};

constexpr float DEG_TO_RAD(float angle)
{
    return (angle * M_PI_F) / 180.0f;
};

float V2fLengthSquared(const Vec2& v)
{
    return v.x * v.x + v.y * v.y;
}

float V2fLength(const Vec2& v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}

Vec2 V2fNormalize(const Vec2& v)
{
    if (V2fLengthSquared(v) == 0)
        return v;
    else
        return v / V2fLength(v);
}

float V2fDot(const Vec2& v1, const Vec2& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

float V2fCross(const Vec2& v1, const Vec2& v2)
{
    return v1.x * v2.y - v1.y * v2.x;
}