#pragma once
#include <math.h>
#include <SFML/System/Vector2.hpp>
#include <box2d/b2_math.h>
#include <yaml-cpp/yaml.h>

namespace Engine
{
    namespace math
    {
        const float M_PI_F = 3.14159274101257324219f;

        using Vec2 = b2Vec2;

        float RAD_TO_DEG(float angle);

        float DEG_TO_RAD(float angle);

        float AngleBetweenVecs(Vec2 a, Vec2 b);

        float V2fLengthSquared(const Vec2& v);
        float V2FDistanceSquared(const Vec2& a, const Vec2& b);
        float V2fLength(const Vec2& v);

        Vec2 V2fNormalize(const Vec2& v);

        float V2fDot(const Vec2& v1, const Vec2& v2);

        float V2fCross(const Vec2& v1, const Vec2& v2);
        float V2fCross(const Vec2& v1, const Vec2& v2);
    };
};

namespace YAML {
	template<>
	struct convert<sf::Vector2i> {
		static Node encode(const sf::Vector2i& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			return node;
		}

		static bool decode(const Node& node, sf::Vector2i& rhs) {
			if (!node.IsSequence() || node.size() != 2) {
				return false;
			}

			rhs.x = node[0].as<int>();
			rhs.y = node[1].as<int>();
			return true;
		}
	};
}