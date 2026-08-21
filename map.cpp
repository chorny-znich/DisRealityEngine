#include "map.h"
#include "sprite_database.h"
#include "engine_data.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>
#include <fstream>
#include <format>
#include <algorithm>
#include <memory>

namespace dr
{
    void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
      // Prepare a light map
      sf::BlendMode subtractAlpha;
      subtractAlpha.colorSrcFactor = sf::BlendMode::Factor::Zero;
      subtractAlpha.colorDstFactor = sf::BlendMode::Factor::One;
      subtractAlpha.colorEquation = sf::BlendMode::Equation::Add;
      subtractAlpha.alphaSrcFactor = sf::BlendMode::Factor::SrcAlpha;
      subtractAlpha.alphaDstFactor = sf::BlendMode::Factor::One;
      subtractAlpha.alphaEquation = sf::BlendMode::Equation::ReverseSubtract;

      mLightMapTexture.clear(sf::Color(15, 15, 25, 235));
      const sf::Texture& lightTexture = dr::Textures::get("light_texture");
      std::unique_ptr<sf::Sprite> lightSprite = std::make_unique<sf::Sprite>(lightTexture);
      lightSprite->setOrigin({128.f, 128.f});
      lightSprite->setPosition({ 100.f, 100.f });

      sf::RenderStates lightSourceStates;
      lightSourceStates.blendMode = subtractAlpha;
      lightSourceStates.transform = states.transform;
      mLightMapTexture.draw(*lightSprite, lightSourceStates);
      mLightMapTexture.display();

      // Draw floor layer
      states.texture = &Textures::get(mFloorTextureId);
      target.draw(mFloorMap, states);
      states.texture = nullptr;

        for (const auto& obj : mArchitecture)
        {
          target.draw(*obj, states);
        }

        for (const auto& obj : mDecorations)
        {
          target.draw(*obj, states);
        }

        // Draw a light map
        if (mLightMapSprite != nullptr)
        {
          sf::RenderStates mapLightStates = states;
          //mapLightStates.transform = sf::Transform::Identity;
          mapLightStates.blendMode = sf::BlendMultiply;
          target.draw(*mLightMapSprite, mapLightStates);
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
                loc.mPosition = { static_cast<uint16_t>(x), static_cast<uint16_t>(y) };
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
    
    /**
     * @brief 
     * @param index 
     * @param id 
     */
    void Map::updateFloorMap(uint16_t index, uint16_t id)
    {
        sf::Vector2f textCoord = SpriteDatabase::instance().getSpriteCoords(id);
        int pos = static_cast<int>(index) * 6;
        mFloorMap[pos + 0].texCoords = sf::Vector2f(textCoord.x, textCoord.y);
        mFloorMap[pos + 1].texCoords = sf::Vector2f(textCoord.x + mTileSize.x,
            textCoord.y);
        mFloorMap[pos + 2].texCoords = sf::Vector2f(textCoord.x + mTileSize.x,
          textCoord.y + mTileSize.y);
        mFloorMap[pos + 3].texCoords = sf::Vector2f(textCoord.x + mTileSize.x,
          textCoord.y + mTileSize.y);
        mFloorMap[pos + 4].texCoords = sf::Vector2f(textCoord.x,
          textCoord.y + mTileSize.y);
        mFloorMap[pos + 5].texCoords = sf::Vector2f(textCoord.x, textCoord.y);
    }
    
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
    void Map::createArchitectureLayer()
    {
        for (auto& loc : mLocations) 
        {
            if (loc.mArchitectureLayerId != 0) 
            {
                loc.mEmpty = false;
                mArchitecture.push_back(std::move(createArchitectureActor(loc.mId)));
            }
        }
    }
    
    /**
     * @brief 
     */
    void Map::createDecorationLayer()
    {
        for (auto& loc : mLocations) 
        {
            if (loc.mDecorationLayerId != 0) 
            {
                loc.mEmpty = false;
                mDecorations.push_back(std::move(createDecorationActor(loc.mId)));
            }
        }
    }
    /*
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
    
    /**
     * @brief 
     * @param id 
     * @return  
     */
    ArchitectureActorPtr Map::createArchitectureActor(uint16_t id)
    {
        Location& loc = getLocation(id);
        SpriteInfo info = SpriteDatabase::instance().getSpriteInfo(loc.mArchitectureLayerId);
        sf::Texture& texture = Textures::get(info.textureId);
        sf::IntRect rect = { {static_cast<int>(info.x), static_cast<int>(info.y)},
          {static_cast<int>(mTileSize.x), static_cast<int>(mTileSize.y)} };
        
        std::unique_ptr<ArchitectureActor> architectureActor = std::make_unique<ArchitectureActor>(id, rect, texture);
        architectureActor->setPosition({ loc.mPosition.x * mTileSize.x, loc.mPosition.y * mTileSize.y });

        return architectureActor;
    }

    /**
     * @brief 
     * @param lop Pointer to the object of the level architecture 
     */
    void Map::addArchitectureActor(ArchitectureActorPtr lop)
    {
      mArchitecture.push_back(std::move(lop));
    }
    
    void Map::deleteArchitectureActor(uint16_t id)
    {
        mArchitecture.erase(std::remove_if(mArchitecture.begin(), mArchitecture.end(), [id](auto& obj) {
            return obj->getID() == id;
            }), mArchitecture.end());
    }

    DecorationActorPtr Map::createDecorationActor(uint16_t id)
    {
        Location& loc = getLocation(id);
        SpriteInfo info = SpriteDatabase::instance().getSpriteInfo(loc.mDecorationLayerId);
        sf::Texture& texture = Textures::get(info.textureId);
        sf::IntRect rect = { {static_cast<int>(info.x), static_cast<int>(info.y)},
           {static_cast<int>(mTileSize.x), static_cast<int>(mTileSize.y)} };
        
        std::unique_ptr<DecorationActor> decorationActor = std::make_unique<DecorationActor>(id, rect, texture);
        decorationActor->setPosition({ loc.mPosition.x * mTileSize.x, loc.mPosition.y * mTileSize.y });

        return decorationActor;
    }

    void Map::addDecorationActor(DecorationActorPtr dap)
    {
        mDecorations.push_back(std::move(dap));
    }

    void Map::deleteDecorationActor(uint16_t id)
    {
        mDecorations.erase(std::remove_if(mDecorations.begin(), mDecorations.end(), [id](auto& obj) {
            return obj->getID() == id;
            }), mDecorations.end());
    }

    const std::vector<Location>& Map::getLocations() const
    {
        return mLocations;
    }

    /**
     * @brief Initialize the lighting map
     * @param windowSize Display size 
     */
    void Map::initLighting(sf::Vector2u windowSize)
    {
      (void)mLightMapTexture.resize(windowSize);
      mLightMapSprite = std::make_unique<sf::Sprite>(mLightMapTexture.getTexture());
    }
}