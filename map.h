#pragma once
#include "location.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <cstdint>
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
	class Map
	{
    private:
        uint16_t mMapIndex{ 0 };
        sf::Vector2u mMapSize{ 3, 3 };
        sf::VertexArray mFloorMap;
        //LevelObjects mLevelObjects;
        //StaticObjects mStaticObjects;
        std::vector<Location> mLocations;
        //std::unordered_map<uint16_t, MapEntry> mEntries;

        void setMapIndex(uint16_t index);
        void setMapSize(sf::Vector2u size);

        //size_t findEntryId(sf::Vector2u pos) const;

    public:
        void createMap(uint16_t index, sf::Vector2u size, uint16_t groundLayerId);
        void createFloorMap();
        void updateFloorMap(uint16_t index, uint16_t id);
        const sf::VertexArray& getFloorMap() const;
        //void createLevelObjects();
        //void createStaticObjects();
        //LevelObjects& getLevelObjects();
        //StaticObjects& getStaticObjects();
        uint16_t getMapIndex() const;
        sf::Vector2u getMapSize() const;
        Location& getLocation(size_t id);
        //LevelObjectPtr createLevelObject(size_t id);
        //void addLevelObject(LevelObjectPtr lop);
        //void deleteLevelObject(size_t id);
        //StaticObjectPtr createStaticObject(size_t id);
        //void addStaticObject(StaticObjectPtr sop);
        //void deleteStaticObject(size_t id);
        //void createEntry(size_t id, MapEntry entry);
        //void deleteEntry(size_t id);
        //void saveEntries(const std::string& filename);
        //void loadEntries(const std::string& filename);
        //MapEntry& getEntry(sf::Vector2u pos);
        //MapEntry& getEntry(size_t id);
        //const std::map<size_t, MapEntry>& getEntries() const;
        //size_t getNumberOfEntries() const;
        const std::vector<Location>& getLocations() const;
	};
}

