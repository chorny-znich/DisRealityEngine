#include "tile_database.h"
#include "ini_parser.h"
#include "engine_data.h"
#include <charconv>

namespace dr
{
	void TileDatabase::init()
	{
        IniDocument doc = loadIniDocument(path::TileMap.data());
        Section tileSizeSection = doc.getSection("tile_size");
        mTileSize = {std::stoi(tileSizeSection.at("width")), std::stoi(tileSizeSection.at("height"))};
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

    sf::Vector2f TileDatabase::getSpriteCoords(uint16_t id) const
    {
        return { mTileMap.at(id).x, mTileMap.at(id).y };
    }

    /**
     * @brief Create a sf::Sprite
     * @return  
     */
    sf::Sprite TileDatabase::getSprite(uint16_t id) const
    {
      Tile tile = getTile(id);
      sf::Sprite sprite(dr::Textures::get(tile.mTextureId));
      sprite.setTextureRect({ { static_cast<int>(getSpriteCoords(id).x), static_cast<int>(getSpriteCoords(id).y) },
        { mTileSize.x, mTileSize.y }});
      return sprite;
    }

    Tile TileDatabase::getTile(uint16_t id) const
    {
        return mTileMap.at(id);
    }
}