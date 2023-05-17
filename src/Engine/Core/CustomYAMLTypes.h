#pragma once

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