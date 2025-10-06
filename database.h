#pragma once
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace dr
{
  struct Tile {
    std::string mSpriteId;
    std::string mTextureId;
    float x;
    float y;
  };

  /**
   * @brief Database for the all engine components
  */
  class Database
  {
  private:
    static Database* mpInstance;
    std::unordered_map<std::string, Tile> mTextureMap;
  public:
    Database();
    void init();
    static sf::Vector2f getSprite(const std::string& id);
    static Tile getTile(const std::string& id);
  };
}