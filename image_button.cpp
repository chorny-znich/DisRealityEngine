#include "image_button.h"
#include "sprite_database.h"

namespace dr
{
  /**
   * @brief 
   * @param size 
   * @param sprite 
   */
  dr::ImageButton::ImageButton(sf::Vector2f size, uint16_t spriteID) :
    Button(size),
    mSprite(dr::SpriteDatabase::instance().getSprite(spriteID))
  {
    //mSprite = std::make_unique<sf::Sprite>(dr::SpriteDatabase::instance().getSprite(spriteID));
  }
}