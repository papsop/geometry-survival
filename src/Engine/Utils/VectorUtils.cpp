#include "VectorUtils.h"

namespace Engine
{
    namespace math
    {
        const int PixelsPerMeter = 50;

        float RAD_TO_DEG(float angle)
        {
            return angle * (180.0f / M_PI_F);
        };

        float DEG_TO_RAD(float angle)
        {
            return angle * (M_PI_F / 180.0f);
        };

				Engine::math::Vec2 GetVectorFromAngle(float angleRad)
				{
          angleRad += Engine::math::M_PI_F / 2.0f; // need to rotate because 0 angles is 'up' instead of 'right'
          return { cosf(angleRad), sinf(angleRad) };
				}

				float AngleBetweenVecs(Vec2 a, Vec2 b)
        {
            Vec2 AB = b - a;
            return atan2(AB.y, AB.x);
        }

				float AngleOfVec(Vec2 a)
				{
          return atan2(a.y, a.x) - M_PI_F/2.0f;
				}

				float V2fLengthSquared(const Vec2& v)
        {
            return v.x * v.x + v.y * v.y;
        }

        float V2FDistanceSquared(const Vec2& a, const Vec2& b)
        {
          return V2fLengthSquared(b-a);
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
            {
                auto length = V2fLength(v);
                return {v.x/length, v.y/length};
            }
        }

        float V2fDot(const Vec2& v1, const Vec2& v2)
        {
            return v1.x * v2.x + v1.y * v2.y;
        }

        float V2fCross(const Vec2& v1, const Vec2& v2)
        {
            return v1.x * v2.y - v1.y * v2.x;
        }

				float RandomFloatBetween(float min, float max)
				{
          return min + static_cast<float>(rand()) * static_cast<float>(max - min) / RAND_MAX;
				}

		};
};