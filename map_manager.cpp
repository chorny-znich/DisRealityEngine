#include "map_manager.h"
#include "map.h"
#include "sprite_database.h"
#include "ini_parser.h"
#include "engine_data.h"
#include <format>
#include <SFML/System/Vector2.hpp>

namespace dr
{
	void dr::MapManager::loadMap(uint16_t mapIndex)
	{
        auto iter = mMaps.find(mapIndex);
        if (iter == mMaps.end())
        {
            mMaps[mapIndex] = std::make_unique<Map>();
            Map& currentMap = *mMaps[mapIndex];
            
            const std::string filename = std::format("{}map_{}.ini", path::MapsFolder, mapIndex);
            IniDocument doc = loadIniDocument(filename);
            Section mapInfoSection = doc.getSection("map_info");
            currentMap.setMapIndex(static_cast<uint16_t>(std::stoul(mapInfoSection.at("id"))));
            Section section = doc.getSection("map_size");
            const sf::Vector2u mapSize = { static_cast<uint16_t>(std::stoul(section.at("width"))), 
                static_cast<uint16_t>(std::stoul(section.at("height"))) };
            currentMap.setMapSize(mapSize);

            for (size_t y = 0; y < mapSize.y; y++) {
                for (size_t x = 0; x < mapSize.x; x++) {
                    Section section = doc.getSection(std::format("loc_{}_{}", y, x));
                    Location loc;
                    loc.mId = static_cast<uint16_t>(y * mapSize.x + x);
                    loc.mPosition = { static_cast<int16_t>(x), static_cast<int16_t>(y) };
                    loc.mFloorLayerId = static_cast<uint16_t>(std::stoul(section.at("floor_layer")));
                    loc.mArchitectureLayerId = static_cast<uint16_t>(std::stoul(section.at("architecture_layer")));
                    loc.mDecorationLayerId = static_cast<uint16_t>(std::stoul(section.at("decoration_layer")));
                    loc.mPassable = std::stoi(section.at("passable"));
                    loc.isTransfer = std::stoi(section.at("is_transfer"));
                    if (loc.isTransfer)
                    {
                      loc.mapTransfer = {static_cast<uint16_t>(std::stoul(section.at("target_map"))), 
                        {std::stoi(section.at("target_x")), std::stoi(section.at("target_y"))}};
                    }
                    mMaps[mapIndex]->addLocation(std::move(loc));
                }
            }
            uint16_t floorSpriteId = currentMap.getLocation(0).mFloorLayerId;
            auto spriteInfo = SpriteDatabase::instance().getSpriteInfo(floorSpriteId);
            currentMap.setFloorTextureId(spriteInfo.textureId);

            mMaps[mapIndex]->createFloorMap();
            mMaps[mapIndex]->createArchitectureLayer();
            mMaps[mapIndex]->createDecorationLayer();
        }

        mCurrentMapIndex = mapIndex;
	}

  /**
   * @brief 
   * @param mapIndex 
   */
  void MapManager::saveMap(const Map& map) const
  {
    dr::IniDocument doc;
    doc.addKeyValuePair("map_info", "id", std::to_string(map.getMapIndex()));
    doc.addKeyValuePair("map_size", "width", std::to_string(map.getMapSize().x));
    doc.addKeyValuePair("map_size", "height", std::to_string(map.getMapSize().y));
    for (const auto& loc : map.getLocations())
    {
      std::string sectionName = std::format("loc_{}_{}", loc.mPosition.y, loc.mPosition.x);
      doc.addKeyValuePair(sectionName, "floor_layer", std::to_string(loc.mFloorLayerId));
      doc.addKeyValuePair(sectionName, "architecture_layer", std::to_string(loc.mArchitectureLayerId));
      doc.addKeyValuePair(sectionName, "decoration_layer", std::to_string(loc.mDecorationLayerId));
      doc.addKeyValuePair(sectionName, "passable", std::to_string(loc.mPassable));
      doc.addKeyValuePair(sectionName, "is_transfer", std::to_string(loc.isTransfer));
      if (loc.isTransfer)
      {
        doc.addKeyValuePair(sectionName, "target_map", std::to_string(loc.mapTransfer.targetMapId));
        doc.addKeyValuePair(sectionName, "target_x", std::to_string(loc.mapTransfer.targetTilePos.x));
        doc.addKeyValuePair(sectionName, "target_y", std::to_string(loc.mapTransfer.targetTilePos.y));
      }
    }
    std::string projectPath = std::filesystem::current_path().string();
    saveIniDocument(std::format("{}/data/maps/map_{}.ini", projectPath, map.getMapIndex()), doc);
  }

  bool MapManager::hasMap(uint16_t mapIndex) const
  {
    return mMaps.contains(mapIndex);
  }

  const Map& MapManager::getCurrentMap() const
  {
      return *mMaps.at(mCurrentMapIndex);
  }

    //
	Map& dr::MapManager::getCurrentMap()
	{
		return *mMaps.at(mCurrentMapIndex);
	}

	uint16_t dr::MapManager::getCurrentMapIndex() const
	{
		return mCurrentMapIndex;
	}
}
