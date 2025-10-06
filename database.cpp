#include "database.h"
#include <cassert>
#include "engine_data.h"
#include "ini_parser.h"

namespace dr
{
  Database* Database::mpInstance{ nullptr };

  Database::Database()
  {
    assert(mpInstance == nullptr);
    mpInstance = this;
  }

  void Database::init()
  {
    auto textureMap = mpInstance->mTextureMap;

    IniDocument doc = loadIniDocument(path::TextureMap);
    Section section = doc.getSection("size");
    const size_t TEXTURE_MAP_SIZE = std::stoul(section.at("size"));
    for (size_t i = 0; i < TEXTURE_MAP_SIZE; i++) {
      Section section = doc.getSection("sprite_" + std::to_string(i + 1));
      Tile tile;
      tile.mSpriteId = section.at("sprite");
      tile.mTextureId = section.at("texture");
      tile.x = std::stof(section.at("x"));
      tile.y = std::stof(section.at("y"));
      mTextureMap.insert({tile.mSpriteId, tile});
    }
  }
  sf::Vector2f Database::getSprite(const std::string& id)
  {
    auto textureMap = mpInstance->mTextureMap;
    return { textureMap.at(id).x, textureMap.at(id).y };
  }
  Tile Database::getTile(const std::string& id)
  {
    auto textureMap = mpInstance->mTextureMap;
    return textureMap.at(id);
  }
}