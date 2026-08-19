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
    ImageButton(sf::Vector2f size, uint16_t spriteID, uint16_t overlapSpriteID);
    void setPosition(sf::Vector2f pos) override;

    virtual bool isOverlap(sf::Vector2f pos) override;
    virtual bool isClicked(sf::Vector2f pos) override;
    virtual void render(sf::RenderWindow& window) override;
  private:
    //std::unique_ptr<sf::Sprite> mSprite{ nullptr };
    sf::Sprite mSprite;
    sf::Sprite mOverlapSprite;
    sf::Sprite mCurrentSprite;
    bool mIsOverlap{ false };
  };
}