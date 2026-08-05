#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
#include <memory>

namespace dr
{
	class Map;

	class MapManager
	{
	public:
		void loadMap(uint16_t mapIndex);
		void saveMap(const Map& map) const;
		bool hasMap(uint16_t mapIndex) const ;
		const Map& getCurrentMap() const;
		Map& getCurrentMap();
		uint16_t getCurrentMapIndex() const;
	private:
		uint16_t mCurrentMapIndex{ 1 };
		std::unordered_map<uint16_t, std::unique_ptr<Map>> mMaps;
	};
}