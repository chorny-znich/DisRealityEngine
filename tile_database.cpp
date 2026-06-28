#include "tile_database.h"
#include "ini_parser.h"
#include "engine_data.h"
#include <charconv>

namespace dr
{
	void TileDatabase::init()
	{
        IniDocument doc = loadIniDocument(path::TileMap.data());
        Section section = doc.getSection("size");
        const size_t TEXTURE_MAP_SIZE = std::stoul(section.at("size"));
        for (size_t i = 0; i < TEXTURE_MAP_SIZE; i++) {
            Section section = doc.getSection("sprite_" + std::to_string(i + 1));
            Tile tile;
            tile.mSpriteId = static_cast<uint16_t>(std::stoul(section.at("sprite")));
            tile.mTextureId = section.at("texture");
            tile.x = std::stof(section.at("x"));
            tile.y = std::stof(section.at("y"));
            mTileMap.insert({ tile.mSpriteId, tile });
        }
	}

    sf::Vector2f TileDatabase::getSprite(uint16_t id) const
    {
        return { mTileMap.at(id).x, mTileMap.at(id).y };
    }

    Tile TileDatabase::getTile(uint16_t id) const
    {
        return mTileMap.at(id);
    }
}