#include "map.h"
#include "sprite_database.h"
#include "engine_data.h"
#include <fstream>
#include <format>
#include <algorithm>

namespace dr
{
    void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.texture = &Textures::get(mFloorTextureId);
        target.draw(mFloorMap, states);
        states.texture = nullptr;

        for (const auto& obj : mLevelObjects)
        {
          target.draw(*obj, states);
        }
    }

    void Map::createMap(uint16_t index, sf::Vector2u size, uint16_t groundLayerId)
    {
        setMapIndex(index);
        setMapSize(size);
        mLocations.reserve(mMapSize.x * mMapSize.y);
        for (size_t y{ 0 }; y < mMapSize.y; y++) {
            for (size_t x{ 0 }; x < mMapSize.x; x++) {
                Location loc;
                loc.mId = static_cast<uint16_t>(y * mMapSize.x + x);
                loc.mFloorLayerId = groundLayerId;
                mLocations.emplace_back(loc);
            }
        }
        createFloorMap();
    }

    void Map::createFloorMap()
    {
        const int VERTEX_IN_QUAD = 6;

        int vertexCounter = 0;
        mFloorMap.setPrimitiveType(sf::PrimitiveType::Triangles);
        mFloorMap.resize(mMapSize.x * mMapSize.y * VERTEX_IN_QUAD);

        for (size_t y{ 0 }; y < mMapSize.y; y++) {
            for (size_t x{ 0 }; x < mMapSize.x; x++) {
                mFloorMap[vertexCounter + 0].position = sf::Vector2f(x * mTileSize.x, y * mTileSize.y);
                mFloorMap[vertexCounter + 1].position = sf::Vector2f(x * mTileSize.x + mTileSize.x,
                    y * mTileSize.y);
                mFloorMap[vertexCounter + 2].position = sf::Vector2f(x * mTileSize.x + mTileSize.x,
                    mTileSize.y + y * mTileSize.y);
                mFloorMap[vertexCounter + 3].position = sf::Vector2f(x * mTileSize.x + mTileSize.x,
                    y * mTileSize.y + mTileSize.y);
                mFloorMap[vertexCounter + 4].position = sf::Vector2f(x * mTileSize.x,
                    y * mTileSize.y + mTileSize.y);
                mFloorMap[vertexCounter + 5].position = sf::Vector2f(x * mTileSize.x, y * mTileSize.y);

                const uint16_t id = mLocations.at(y * mMapSize.x + x).mFloorLayerId;
                sf::Vector2f textCoord = SpriteDatabase::instance().getSpriteCoords(id);
                mFloorMap[vertexCounter + 0].texCoords = sf::Vector2f(textCoord.x, textCoord.y);
                mFloorMap[vertexCounter + 1].texCoords = sf::Vector2f(textCoord.x + mTileSize.x,
                    textCoord.y);
                mFloorMap[vertexCounter + 2].texCoords = sf::Vector2f(textCoord.x + mTileSize.x,
                    textCoord.y + mTileSize.y);
                mFloorMap[vertexCounter + 3].texCoords = sf::Vector2f(textCoord.x + mTileSize.x,
                    textCoord.y + mTileSize.y);              
                mFloorMap[vertexCounter + 4].texCoords = sf::Vector2f(textCoord.x,
                    textCoord.y + mTileSize.y);
                mFloorMap[vertexCounter + 5].texCoords = sf::Vector2f(textCoord.x, textCoord.y);
                
                vertexCounter += VERTEX_IN_QUAD;
            }
        }
    }
    /*
    void Map::updateFloorMap(size_t index, const std::string& id)
    {
        sf::Vector2f textCoord = dr::Database::getSprite(id);
        int pos = static_cast<int>(index) * 4;
        mFloorMap[pos + 0].texCoords = sf::Vector2f(textCoord.x, textCoord.y);
        mFloorMap[pos + 1].texCoords = sf::Vector2f(textCoord.x + mTileSize.x,
            textCoord.y);
        mFloorMap[pos + 2].texCoords = sf::Vector2f(textCoord.x + mTileSize.x,
            textCoord.y + mTileSize.y);
        mFloorMap[pos + 3].texCoords = sf::Vector2f(textCoord.x,
            textCoord.y + mTileSize.y);
    }
    */
    void Map::setMapIndex(uint16_t index)
    {
        mMapIndex = index;
    }

    void Map::setMapSize(sf::Vector2u size)
    {
        mMapSize = size;
    }
    /*
    size_t Map::findEntryId(sf::Vector2u pos) const
    {
        auto iter = std::find_if(mEntries.begin(), mEntries.end(), [pos](const auto& entry) {
            return pos == entry.second.getPosition();
            });
        size_t id = iter->second.getPosition().y * mMapSize.x + iter->second.getPosition().x;
        return id;

    }
   */
    void Map::createLevelObjects()
    {
        for (auto& loc : mLocations) {
            if (loc.mLevelLayerId != 0) {
                loc.mPlaceRandomObject = false;
                mLevelObjects.push_back(std::move(createLevelObject(loc.mId)));
            }
        }
    }
    /*
    void Map::createStaticObjects()
    {
        for (auto& loc : mLocations) {
            if (loc.getObjectLayerId() != "none") {
                loc.changePlacementStatus(false);
                mStaticObjects.push_back(std::move(createStaticObject(loc.getId())));
            }
        }
    }

    LevelObjects& Map::getLevelObjects()
    {
        return mLevelObjects;
    }
    StaticObjects& Map::getStaticObjects()
    {
        return mStaticObjects;
    }
    */

    uint16_t Map::getMapIndex() const
    {
        return mMapIndex;
    }

    sf::Vector2u Map::getMapSize() const
    {
        return mMapSize;
    }

    void Map::setTileSize(sf::Vector2f tileSize)
    {
        mTileSize = tileSize;
    }

    void Map::setFloorTextureId(const std::string& id)
    {
        mFloorTextureId = id;
    }

    void Map::addLocation(Location loc)
    {
        mLocations.push_back(std::move(loc));
    }

    Location& Map::getLocation(uint16_t id)
    {
        return mLocations.at(id);
    }
    
    // Create a single LevelObject
    std::shared_ptr<LevelObject> Map::createLevelObject(uint16_t id)
    {
        Location& loc = getLocation(id);
        SpriteInfo info = SpriteDatabase::instance().getSpriteInfo(loc.mLevelLayerId);
        sf::Texture& texture = Textures::get(info.textureId);
        sf::IntRect rect = { {static_cast<int>(info.x), static_cast<int>(info.y)},
          {static_cast<int>(mTileSize.x), static_cast<int>(mTileSize.y)} };
        
        std::shared_ptr<LevelObject> pLevelObject = std::make_shared<LevelObject>(id, rect, texture);
        pLevelObject->setPosition({ loc.mPosition.x * mTileSize.x, loc.mPosition.y * mTileSize.y });;

        return pLevelObject;
    }
    /*
    void Map::addLevelObject(LevelObjectPtr lop)
    {
        mLevelObjects.push_back(lop);
    }

    void Map::deleteLevelObject(size_t id)
    {
        mLevelObjects.erase(std::remove_if(mLevelObjects.begin(), mLevelObjects.end(), [id](auto& obj) {
            return obj->getId() == id;
            }), mLevelObjects.end());
    }

    StaticObjectPtr Map::createStaticObject(size_t id)
    {
        Location loc = getLocation(id);
        Tile tile = dr::Database::getTile(loc.getObjectLayerId());
        sf::Sprite sprite;
        sprite.setTexture(Textures::get(tile.mTextureId));
        sprite.setTextureRect({ static_cast<int>(dr::Database::getSprite(tile.mSpriteId).x),
          static_cast<int>(dr::Database::getSprite(tile.mSpriteId).y), static_cast<int>(mTileSize.x),
          static_cast<int>(mTileSize.y) });
        sprite.setPosition({ loc.getPosition().x * mTileSize.x, loc.getPosition().y * mTileSize.y });
        std::shared_ptr<StaticObject> pStaticObject = std::make_shared<StaticObject>(sprite);
        pStaticObject->setId(id);

        return pStaticObject;
    }

    void Map::addStaticObject(StaticObjectPtr sop)
    {
        mStaticObjects.push_back(sop);
    }

    void Map::deleteStaticObject(size_t id)
    {
        mStaticObjects.erase(std::remove_if(mStaticObjects.begin(), mStaticObjects.end(), [id](auto& obj) {
            return obj->getId() == id;
            }), mStaticObjects.end());
    }

    void Map::createEntry(size_t id, MapEntry entry)
    {
        mEntries.emplace(id, entry);
    }
    void Map::deleteEntry(size_t id)
    {
        mEntries.erase(id);
    }

   */

    const std::vector<Location>& Map::getLocations() const
    {
        return mLocations;
    }

    /*
    MapEntry& Map::getEntry(sf::Vector2u pos)
    {
        return mEntries.at(findEntryId(pos));
    }

    MapEntry& Map::getEntry(size_t id)
    {
        return mEntries.at(id);
    }

    const std::map<size_t, MapEntry>& Map::getEntries() const
    {
        return mEntries;
    }

    size_t Map::getNumberOfEntries() const
    {
        return mEntries.size();
    }*/
}