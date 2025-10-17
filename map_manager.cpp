#include "map_manager.h"
#include "map.h"
#include "map_entry.h"
#include <format>

namespace dr
{
  MapManager::MapManager(size_t numberOfMaps) :
    NUMBER_OF_MAPS{ numberOfMaps }
  {
  }

  void MapManager::init()
  {
    for (size_t i{ 1 }; i <= NUMBER_OF_MAPS; i++) {
      std::shared_ptr<Map> newMap = std::make_shared<Map>();
      newMap->loadFromFile(std::format("data/maps/map_{}.ini", i));
      newMap->loadEntries(std::format("data/maps/entry_{}.ini", i));
      mMaps.insert({ i, std::move(newMap) });
    }
  }

  std::shared_ptr<Map> MapManager::getCurrentMap()
  {
    return mMaps.at(mCurrentMapIndex);
  }
  void MapManager::setCurrentMapIndex(size_t index)
  {
    mCurrentMapIndex = index;
  }
}