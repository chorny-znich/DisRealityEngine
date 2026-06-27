#pragma once

/**
 * @brief map's unit, usually a tile. The set of locations forms level's map.
*/

namespace dr
{
	struct Location
	{
		uint16_t mId;
		uint16_t mFloorLayerId{0};
		uint16_t mLevelLayerId{0};
		uint16_t mObjectLayerId{0};
		bool mPassable{ true };
		bool mEntry{ false };
		bool mPlaceRandomObject{ true };
	};
}