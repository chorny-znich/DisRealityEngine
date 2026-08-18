#pragma once
#include "button.h"

namespace dr
{
  /**
   * @brief Button with image on it
   */
  class ImageButton : public Button
  {
  public:
    ImageButton(sf::Vector2f size, uint16_t spriteID);
  private:
    //std::unique_ptr<sf::Sprite> mSprite{ nullptr };
    sf::Sprite mSprite;
  };
}