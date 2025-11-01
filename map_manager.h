#pragma once
#include <memory>
#include <unordered_map>
#include <SFML/System.hpp>

namespace dr
{
	class Map;
	class MapEntry;

	class MapManager
	{
	private:
		const size_t NUMBER_OF_MAPS;
		const sf::Vector2f TILE_SIZE{ 128.f, 128.f };
		size_t mCurrentMapIndex{ 1 };
		std::unordered_map<size_t, std::shared_ptr<Map>> mMaps;
		std::unordered_map<std::string, sf::Vector2u> mEntryPosition;
		//std::map <size_t, bool> mVisitedMaps;
	public:
		MapManager(size_t numberOfMaps);
		void init();
		std::shared_ptr<Map> getCurrentMap();
		sf::Vector2u getEntryPosition(const std::string& id);
		//void setPlayerSpawnPosition(sf::Vector2u pos);
		//sf::Vector2u getPlayerSpawnPosition();
		void setCurrentMapIndex(size_t index);
		size_t getCurrentMapIndex() const;
		/*
		void setVisited();
		bool isVisited() const;*/
	};
}