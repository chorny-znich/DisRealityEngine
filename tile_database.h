#pragma once
#include <string>
#include <unordered_map>
#include <cstdint>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>

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
		sf::Vector2f getSpriteCoords(uint16_t id) const;
		sf::Sprite getSprite(uint16_t id) const;
		Tile getTile(uint16_t id) const;
	private:
		sf::Vector2i mTileSize{ 0, 0 };
		std::unordered_map<uint16_t, Tile> mTileMap;
	};
}