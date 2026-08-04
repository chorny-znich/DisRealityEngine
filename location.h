#pragma once
#include <cstdint>
#include <SFML/System/Vector2.hpp>

/**
 * @brief map's unit, usually a tile. The set of locations forms level's map.
*/

namespace dr
{
	struct Location
	{
		uint16_t mId{ 0 };
		sf::Vector2u mPosition{ 0, 0 };
		uint16_t mFloorLayerId{0};
		uint16_t mArchitectureLayerId{0};
		uint16_t mDecorationLayerId{0};
		bool mPassable{ true };
		bool mEntry{ false };
		bool mPlaceRandomObject{ true };
	};
}