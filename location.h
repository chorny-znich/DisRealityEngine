#pragma once

/**
 * @brief map's unit, usually a tile. The set of locations forms level's map.
*/

namespace dr
{
	struct Location
	{
		uint16_t mId;
		uint16_t mFloorLayerId;
		uint16_t mLevelLayerId;
		uint16_t mObjectLayerId;
		bool mPassable{ true };
		bool mEntry{ false };
		bool mPlaceRandomObject{ true };
	};
}