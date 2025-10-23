#pragma once
#include "location.h"
#include "map_entry.h"
#include "level_object.h"
#include "static_object.h"
#include <unordered_map>
#include <map>
#include <SFML/Graphics.hpp>

/**
 * @brief Game's map
 * Has layers:
 * Ground layer as a vertex array
 * Level layer as a architecture of the map
 * Static layer as objects that can have animation but don't move 
*/
namespace dr
{
  class Map
  {
  private:
    int mMapIndex{ 0 };
    sf::Vector2i mMapSize{ 3, 3 };
    sf::VertexArray mFloorMap;
    LevelObjects mLevelObjects;
    StaticObjects mStaticObjects;
    std::vector<Location> mLocations;
    std::map<size_t, MapEntry> mEntries;

    void setMapIndex(int index);
    void setMapSize(sf::Vector2i size);

    size_t findEntryId(sf::Vector2u pos) const;
  
  public:
    void createMap(int index, sf::Vector2i size, const std::string& groundLayerId);
    void createFloorMap();
    void updateFloorMap(size_t index, const std::string& id);
    const sf::VertexArray& getFloorMap() const;
    void createLevelObjects();
    void createStaticObjects();
    LevelObjects& getLevelObjects();
    StaticObjects& getStaticObjects();
    //void update(sf::Time dt);
    size_t getMapIndex() const;
    sf::Vector2i getMapSize() const;
    Location& getLocation(size_t id);
    LevelObjectPtr createLevelObject(size_t id);
    void addLevelObject(LevelObjectPtr lop);
    void deleteLevelObject(size_t id);
    StaticObjectPtr createStaticObject(size_t id);
    void addStaticObject(StaticObjectPtr sop);
    void deleteStaticObject(size_t id);
    void createEntry(size_t id, MapEntry entry);
    void deleteEntry(size_t id);
    void saveEntries(const std::string& filename);
    void loadEntries(const std::string& filename);
    MapEntry& getEntry(sf::Vector2u pos);
    MapEntry& getEntry(size_t id);
    const std::map<size_t, MapEntry>& getEntries() const;
    size_t getNumberOfEntries() const;
    void saveMap(const std::string& filename);
    //sf::Vector2f getTileSize() const;
    void loadFromFile(const std::string& filename);
  };
}