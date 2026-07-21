#include "sprite_database.h"
#include "ini_parser.h"
#include "engine_data.h"
#include <vector>
#include <charconv>

namespace dr
{
	void SpriteDatabase::init()
	{
    std::unordered_map<std::string, SpriteCategory> idToType
    {
      {"floor", SpriteCategory::Floor},
      {"wall", SpriteCategory::Wall},
      {"decoration", SpriteCategory::Decoration},
      {"item", SpriteCategory::Item},
      {"ui", SpriteCategory::UI},
      {"unknown", SpriteCategory::Unknown}
    };

    IniDocument doc = loadIniDocument(path::TileMap.data());
    Section tileSizeSection = doc.getSection("tile_size");
    mTileSize = {std::stoi(tileSizeSection.at("width")), std::stoi(tileSizeSection.at("height"))};
    Section section = doc.getSection("size");
    const size_t TEXTURE_MAP_SIZE = std::stoul(section.at("size"));
    for (size_t i = 0; i < TEXTURE_MAP_SIZE; i++)
    {
      Section section = doc.getSection("sprite_" + std::to_string(i + 1));
      SpriteInfo info;
      info.spriteId = static_cast<uint16_t>(std::stoul(section.at("sprite")));
      info.textureId = section.at("texture");
      info.x = std::stof(section.at("x"));
      info.y = std::stof(section.at("y"));
      info.type = idToType.at(section.at("type"));
      mSpriteMap.insert({ info.spriteId, info });
    }
	}

    sf::Vector2f SpriteDatabase::getSpriteCoords(uint16_t id) const
    {
        return { mSpriteMap.at(id).x, mSpriteMap.at(id).y };
    }

    /**
     * @brief Create a sf::Sprite
     * @return  
     */
    sf::Sprite SpriteDatabase::getSprite(uint16_t id) const
    {
      SpriteInfo info = getSpriteInfo(id);
      sf::Sprite sprite(dr::Textures::get(info.textureId));
      sprite.setTextureRect({ { static_cast<int>(getSpriteCoords(id).x), static_cast<int>(getSpriteCoords(id).y) },
        { mTileSize.x, mTileSize.y }});
      return sprite;
    }

    SpriteInfo SpriteDatabase::getSpriteInfo(uint16_t id) const
    {
        return mSpriteMap.at(id);
    }

    /**
     * @brief 
     * @param  
     * @return 
     */
    std::vector<std::uint16_t> SpriteDatabase::getIdByCategory(SpriteCategory type)
    {
      std::vector<std::uint16_t> result;
      for (const auto& info : mSpriteMap)
      {
        if (info.second.type == type)
        {
          result.push_back(info.first);
        }
      }
      return result;
    }
}