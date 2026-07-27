#include "cursor_component.h"
#include "sprite_database.h"
#include <algorithm>

namespace dr
{
  CursorComponent::CursorComponent(sf::View& view) :
    mGameView{view},
    mTilePosition{0, 0}
  {
    mSquareCursor = {
        sf::RectangleShape{{mTileSize, CURSOR_WIDTH}},
        sf::RectangleShape{{CURSOR_WIDTH, mTileSize}},
        sf::RectangleShape{{mTileSize, CURSOR_WIDTH}},
        sf::RectangleShape{{CURSOR_WIDTH, mTileSize}}
    };
    changeCursorColor(DEFAULT_CURSOR_COLOR);
  }

  void CursorComponent::init()
  {
    mTileSize = static_cast<float>(dr::SpriteDatabase::instance().getTileSize().x);
  }

  void CursorComponent::handleInput(sf::Vector2i mouseWindowPos, sf::RenderWindow& window)
  {
    mMousePosition = window.mapPixelToCoords(mouseWindowPos, mGameView);
  }

  /**
   * @brief Update the cursor position
   */
  void CursorComponent::update(float dt)
  {
    int rawX = static_cast<int>(mMousePosition.x / mTileSize);
    rawX = std::clamp(rawX, 0, mMapSize.x - 1);
    int rawY = static_cast<int>(mMousePosition.y / mTileSize);
    rawY = std::clamp(rawY, 0, mMapSize.y - 1);
    sf::Vector2i tileCoords = { rawX, rawY };
    mSquareCursor[0].setPosition({ tileCoords.x * mTileSize, tileCoords.y * mTileSize });
    mSquareCursor[1].setPosition({ tileCoords.x * mTileSize, tileCoords.y * mTileSize });
    mSquareCursor[2].setPosition({ tileCoords.x * mTileSize, tileCoords.y * mTileSize + mTileSize });
    mSquareCursor[3].setPosition({ tileCoords.x * mTileSize + mTileSize - CURSOR_WIDTH, tileCoords.y * mTileSize });
    mTilePosition = { tileCoords.x, tileCoords.y };
  }

  /**
   * @brief 
   */
  void CursorComponent::render(sf::RenderWindow& window)
  {
    for (const auto& item : mSquareCursor) 
    {
      window.draw(item);
    }
  }
  
  /**
   * @brief 
   * @return 
   */
  sf::Vector2i CursorComponent::getTilePosition() const
  {
    return mTilePosition;
  }

  /**
   * @brief 
   * @param size 
   */
  void CursorComponent::setMapSize(sf::Vector2i size)
  {
    mMapSize = size;
  }

  /**
   * @brief 
   * @param color as a sf::Color object: red, green, blue components and the alpha channel 
   */
  void CursorComponent::changeCursorColor(sf::Color color)
  {
    for (auto& elem : mSquareCursor) {
      elem.setFillColor(color);
    }
  }
}