#include "map.h"
#include "level_object.h"
#include "static_object.h"
#include "database.h"
#include "engine_data.h"
#include <fstream>

namespace dr
{
  Map::Map()
  {
  }

  void Map::createMap(int index, sf::Vector2i size, const std::string& groundLayerId)
  {
      setMapIndex(index);
      setMapSize(size);
      for (size_t y{ 0 }; y < mMapSize.y; y++) {
          for (size_t x{ 0 }; x < mMapSize.x; x++) {
            Location loc;
            loc.setId(y * mMapSize.x + x);
            loc.setPosition({ static_cast<unsigned int>(x), static_cast<unsigned int>(y) });
            loc.setFloorLayerId(groundLayerId);
            loc.setLevelLayerId("none");
            loc.setObjectLayerId("none");
            loc.setPassability(true);
            mLocations.push_back(std::move(loc));
          }
      }
      createFloorMap();
  }

  void Map::createFloorMap()
  {
      const int VERTEX_IN_QUAD = 4;

      int vertexCounter = 0;
      mFloorMap.setPrimitiveType(sf::Quads);
      mFloorMap.resize(mMapSize.x * mMapSize.y * VERTEX_IN_QUAD);

      for (size_t y{ 0 }; y < mMapSize.y; y++) {
          for (size_t x{ 0 }; x < mMapSize.x; x++) {
              mFloorMap[vertexCounter + 0].position = sf::Vector2f(x * TILE_SIZE.x, y * TILE_SIZE.y);
              mFloorMap[vertexCounter + 1].position = sf::Vector2f(x * TILE_SIZE.x + TILE_SIZE.y,
                  y * TILE_SIZE.y);
              mFloorMap[vertexCounter + 2].position = sf::Vector2f(x * TILE_SIZE.x + TILE_SIZE.x,
                  y * TILE_SIZE.y + TILE_SIZE.y);
              mFloorMap[vertexCounter + 3].position = sf::Vector2f(x * TILE_SIZE.x,
                  y * TILE_SIZE.y + TILE_SIZE.y);

              const std::string id = mLocations.at(y * mMapSize.x + x).getFloorLayerId();
              sf::Vector2f textCoord = Database::getSprite(id);
              mFloorMap[vertexCounter + 0].texCoords = sf::Vector2f(textCoord.x, textCoord.y);
              mFloorMap[vertexCounter + 1].texCoords = sf::Vector2f(textCoord.x + TILE_SIZE.x,
                  textCoord.y);
              mFloorMap[vertexCounter + 2].texCoords = sf::Vector2f(textCoord.x + TILE_SIZE.x,
                  textCoord.y + TILE_SIZE.y);
              mFloorMap[vertexCounter + 3].texCoords = sf::Vector2f(textCoord.x,
                  textCoord.y + TILE_SIZE.y);

              vertexCounter += VERTEX_IN_QUAD;
          }
      }
  }

  void Map::updateFloorMap(size_t index, const std::string& id)
  {
      sf::Vector2f textCoord = dr::Database::getSprite(id);
      int pos = index * 4;
      mFloorMap[pos + 0].texCoords = sf::Vector2f(textCoord.x, textCoord.y);
      mFloorMap[pos + 1].texCoords = sf::Vector2f(textCoord.x + TILE_SIZE.x,
          textCoord.y);
      mFloorMap[pos + 2].texCoords = sf::Vector2f(textCoord.x + TILE_SIZE.x,
          textCoord.y + TILE_SIZE.y);
      mFloorMap[pos + 3].texCoords = sf::Vector2f(textCoord.x,
          textCoord.y + TILE_SIZE.y);
  }

  void Map::setMapIndex(int index)
  {
      mMapIndex = index;
  }

  void Map::setMapSize(sf::Vector2i size)
  {
      mMapSize = size;
  }

  const sf::VertexArray& Map::getFloorMap() const
  {
      return mFloorMap;
  }
  size_t Map::getMapIndex() const
  {
      return mMapIndex;
  }
  sf::Vector2i Map::getMapSize()
  {
      return mMapSize;
  }
  Location& Map::getLocation(size_t id)
  {
      return mLocations.at(id);
  }
  std::unique_ptr<LevelObject> Map::createLevelObject(size_t id)
  {
      Location loc = getLocation(id);
      Tile tile = dr::Database::getTile(loc.getLevelLayerId());
      sf::Sprite sprite;
      sprite.setTexture(Textures::get(tile.mTextureId));
      sprite.setTextureRect({ static_cast<int>(dr::Database::getSprite(tile.mSpriteId).x),
        static_cast<int>(dr::Database::getSprite(tile.mSpriteId).y), static_cast<int>(TILE_SIZE.x),
        static_cast<int>(TILE_SIZE.y) });
      sprite.setPosition({ loc.getPosition().x * TILE_SIZE.x, loc.getPosition().y * TILE_SIZE.y });
      std::unique_ptr<LevelObject> pLevelObject = std::make_unique<LevelObject>(sprite);
      pLevelObject->setId(id);

      return std::move(pLevelObject);
  }
  std::unique_ptr<StaticObject> Map::createStaticObject(size_t id)
  {
      Location loc = getLocation(id);
      Tile tile = dr::Database::getTile(loc.getObjectLayerId());
      sf::Sprite sprite;
      sprite.setTexture(Textures::get(tile.mTextureId));
      sprite.setTextureRect({ static_cast<int>(dr::Database::getSprite(tile.mSpriteId).x),
        static_cast<int>(dr::Database::getSprite(tile.mSpriteId).y), static_cast<int>(TILE_SIZE.x),
        static_cast<int>(TILE_SIZE.y) });
      sprite.setPosition({ loc.getPosition().x * TILE_SIZE.x, loc.getPosition().y * TILE_SIZE.y });
      std::unique_ptr<StaticObject> pStaticObject = std::make_unique<StaticObject>(sprite);
      pStaticObject->setId(id);

      return std::move(pStaticObject);
  }
  void Map::createEntry(size_t id, MapEntry entry)
  {
      mEntries.emplace(id, entry);
  }
  void Map::deleteEntry(size_t id)
  {
      mEntries.erase(id);
  }
 /* std::vector<sf::Sprite> Map::getStaticActors() const
  {
      std::vector<sf::Sprite> result;
      for (const auto loc : mLocations) {
          if (loc.getLevelLayerId() != "none") {
              dr::Tile tile = dr::Database::getTile(loc.getLevelLayerId());
              sf::Sprite sprite;
              sprite.setTexture(Textures::get(tile.mTextureId));
              sprite.setTextureRect({ static_cast<int>(dr::Database::getSprite(tile.mSpriteId).x),
                static_cast<int>(dr::Database::getSprite(tile.mSpriteId).y), static_cast<int>(TILE_SIZE.x),
                static_cast<int>(TILE_SIZE.y) });
              sprite.setPosition({ loc.getPosition().x * TILE_SIZE.x, loc.getPosition().y * TILE_SIZE.y });
              result.push_back(std::move(sprite));
          }
      }
      return result;
  }*/
  void Map::saveMap(const std::string& filename)
  {
      const std::string FILENAME = path::MapsFolder + filename + ".ini";
      std::ofstream ofs(FILENAME);
      if (ofs) {
          ofs << "[map_size]\n";
          ofs << "width=" << mMapSize.x << '\n';
          ofs << "height=" << mMapSize.y << '\n';
          for (size_t i = 0; i < mMapSize.y; i++) {
              for (size_t j = 0; j < mMapSize.x; j++) {
                  ofs << std::format("[loc_{}_{}]\n", i, j);
                  ofs << std::format("floor_layer={}\n", mLocations[i * mMapSize.x + j].getFloorLayerId());
                  ofs << std::format("objects_layer={}\n", mLocations[i * mMapSize.x + j].getLevelLayerId());
                  if (mLocations[i * mMapSize.x + j].isPassable()) {
                      ofs << std::format("passable=1\n");
                  }
                  else {
                      ofs << std::format("passable=0\n");
                  }
              }
          }
      }
      else {
          std::cerr << std::format("can't open file: {}\n\n", FILENAME);
      }
  }

  // load a map from the ini file
  void Map::loadFromFile(const std::string& filename)
  {
      ini::Document doc = ini::load(filename);
      ini::Section mapInfoSection = doc.getSection("map_info");
      mMapIndex = std::stoul(mapInfoSection.at("id"));
      ini::Section section = doc.getSection("map_size");
      mMapSize.x = std::stoul(section.at("width"));
      mMapSize.y = std::stoul(section.at("height"));

      for (size_t y = 0; y < mMapSize.y; y++) {
          for (size_t x = 0; x < mMapSize.x; x++) {
              ini::Section section = doc.getSection("loc_" + std::to_string(y) + "_" + std::to_string(x));
              Location loc;
              loc.setId(y * mMapSize.x + x);
              loc.setPosition({ static_cast<unsigned int>(x), static_cast<unsigned int>(y) });
              loc.setFloorLayerId(section.at("floor_layer"));
              loc.setObjectLayerId(section.at("objects_layer"));
              loc.setPassability(std::stoi(section.at("passable")));
              mLocations.push_back(std::move(loc));
          }
      }
  }

  void Map::saveEntries(const std::string& filename)
  {
      const std::string FILENAME = path::MapsFolder + filename + ".ini";
      std::ofstream ofs(FILENAME);
      if (ofs) {
          ofs << "[general]\n";
          ofs << "number_of_entries=" << mEntries.size() << '\n';
          for (const auto& [key, value] : mEntries) {
              ofs << std::format("[{}]\n", value.getId());
              ofs << std::format("id={}\n", value.getId());
              ofs << std::format("map_id={}\n", value.getPosition().y);
              ofs << std::format("position_x={}\n", value.getPosition().x);
              ofs << std::format("position_y={}\n", value.getPosition().y);
              ofs << std::format("linked_entry_id={}\n", value.getLinkedEntryId());
              //ofs << std::format("visibility={}\n", value.getVisibility());
          }
      }
      else {
          std::cerr << std::format("can't open file: {}\n\n", FILENAME);
      }
  }
  MapEntry& Map::getEntry(size_t id)
  {
      return mEntries.at(id);
  }
  size_t Map::getNumberOfEntries() const
  {
      return mEntries.size();
  }
}