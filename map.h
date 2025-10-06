#pragma once
#include "location.h"
#include "map_entry.h"
#include <unordered_map>
#include <SFML/Graphics.hpp>

/**
 * @brief Game's map
 * Has layers:
 * Ground layer as a vertex array
*/
namespace dr
{
  class LevelObject;
  class StaticObject;

  class Map
  {
  private:
    int mMapIndex{ 0 };
    sf::Vector2i mMapSize{ 3, 3 };
    sf::VertexArray mFloorMap;
    std::vector<Location> mLocations;
    std::unordered_map<size_t, MapEntry> mEntries;

    void setMapIndex(int index);
    void setMapSize(sf::Vector2i size);
  
  public:
    Map();
    void createMap(int index, sf::Vector2i size, const std::string& groundLayerId);
    void createFloorMap();
    void updateFloorMap(size_t index, const std::string& id);
    const sf::VertexArray& getFloorMap() const;
    //void update(sf::Time dt);
    size_t getMapIndex() const;
    sf::Vector2i getMapSize();
    Location& getLocation(size_t id);
    std::unique_ptr<LevelObject> createLevelObject(size_t id);
    std::unique_ptr<StaticObject> createStaticObject(size_t id);
    void createEntry(size_t id, MapEntry entry);
    void deleteEntry(size_t id);
    void saveEntries(const std::string& filename);
    MapEntry& getEntry(size_t id);
    size_t getNumberOfEntries() const;
    //std::vector<sf::Sprite> getStaticActors() const;
    void saveMap(const std::string& filename);
    //sf::Vector2f getTileSize() const;
    void loadFromFile(const std::string& filename);
  };
}