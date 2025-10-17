#pragma once
#include <memory>
#include <unordered_map>
#include <SFML/System.hpp>

namespace dr
{
	class Map;

	class MapManager
	{
	private:
		const size_t NUMBER_OF_MAPS;
		const sf::Vector2f TILE_SIZE{ 128.f, 128.f };
		size_t mCurrentMapIndex{ 1 };
		std::unordered_map<size_t, std::shared_ptr<Map>> mMaps;
		//std::map <size_t, bool> mVisitedMaps;
	public:
		MapManager(size_t numberOfMaps);
		void init();
		std::shared_ptr<Map> getCurrentMap();
		//void setPlayerSpawnPosition(sf::Vector2u pos);
		//sf::Vector2u getPlayerSpawnPosition();
		void setCurrentMapIndex(size_t index);
		/*
		void setVisited();
		bool isVisited() const;*/
	};
}