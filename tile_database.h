#pragma once
#include <string>
#include <unordered_map>
#include <cstdint>
#include <SFML/System/Vector2.hpp>

namespace dr
{
	struct Tile {
		std::uint16_t mSpriteId;
		std::string mTextureId;
		float x;
		float y;
	};

	class TileDatabase
	{
	private:
		TileDatabase() = default;
	public:
		TileDatabase(const TileDatabase&) = delete;
		TileDatabase& operator=(const TileDatabase&) = delete;
		static TileDatabase& instance()
		{
			static TileDatabase database;
			return database;
		}

		void init();
		sf::Vector2f getSprite(uint16_t id) const;
		Tile getTile(uint16_t id) const;
	private:
		std::unordered_map<uint16_t, Tile> mTileMap;
	};
}