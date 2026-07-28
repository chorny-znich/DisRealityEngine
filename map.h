#pragma once
#include "location.h"
#include "level_object.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

namespace dr
{
	/**
	* @brief Game's map
	* Has layers:
	* Ground layer as a vertex array
	* Level layer as a architecture of the map
	* Static layer as objects that can have animation but don't move
	*/
	class Map : public sf::Drawable
	{
    private:
        uint16_t mMapIndex{ 0 };
        sf::Vector2u mMapSize{ 3, 3 };
        sf::Vector2f mTileSize{ 128.f, 128.f };
        std::string mFloorTextureId{};
        sf::VertexArray mFloorMap;
        LevelObjects mLevelObjects;
        //StaticObjects mStaticObjects;
        std::vector<Location> mLocations;
        //std::unordered_map<uint16_t, MapEntry> mEntries;
        //size_t findEntryId(sf::Vector2u pos) const;

    public:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void createMap(uint16_t index, sf::Vector2u size, uint16_t groundLayerId);
        void createFloorMap();
        void updateFloorMap(uint16_t index, uint16_t id);
        void createLevelObjects();
        //void createStaticObjects();
        //LevelObjects& getLevelObjects();
        //StaticObjects& getStaticObjects();
        void setMapIndex(uint16_t index);
        uint16_t getMapIndex() const;
        void setMapSize(sf::Vector2u size);
        sf::Vector2u getMapSize() const;
        void setTileSize(sf::Vector2f tileSize);
        void setFloorTextureId(const std::string& id);
        void addLocation(Location loc);
        Location& getLocation(uint16_t id);
        LevelObjectPtr createLevelObject(uint16_t id);
        //void addLevelObject(LevelObjectPtr lop);
        //void deleteLevelObject(size_t id);
        //StaticObjectPtr createStaticObject(size_t id);
        //void addStaticObject(StaticObjectPtr sop);
        //void deleteStaticObject(size_t id);
        //void createEntry(size_t id, MapEntry entry);
        //void deleteEntry(size_t id);
        //MapEntry& getEntry(sf::Vector2u pos);
        //MapEntry& getEntry(size_t id);
        //const std::map<size_t, MapEntry>& getEntries() const;
        //size_t getNumberOfEntries() const;
        const std::vector<Location>& getLocations() const;

	};
}

