#include "image_button.h"
#include "sprite_database.h"

namespace dr
{
  /**
   * @brief 
   * @param size 
   * @param sprite 
   */
  dr::ImageButton::ImageButton(sf::Vector2f size, uint16_t spriteID, uint16_t overlapSpriteID) :
    Button(size),
    mSprite(dr::SpriteDatabase::instance().getSprite(spriteID)),
    mOverlapSprite(dr::SpriteDatabase::instance().getSprite(overlapSpriteID)),
    mCurrentSprite(mSprite)
  {
    //mSprite = std::make_unique<sf::Sprite>(dr::SpriteDatabase::instance().getSprite(spriteID));
  }

  /**
   * @brief Set button's position on the screen as sf::Vector2f
   * @param pos pair of float coordinates
   */
  void ImageButton::setPosition(sf::Vector2f pos)
  {
    mCurrentSprite.setPosition(pos);
  }

  /**
   * @brief 
   * @param pos 
   * @return 
   */
  bool ImageButton::isOverlap(sf::Vector2f pos)
  {
    bool isCurrentOverlap = mIsOverlap;
    if (mCurrentSprite.getGlobalBounds().contains(pos))
    {
      mIsOverlap = true;
      if (mIsOverlap != isCurrentOverlap)
      {
        mCurrentSprite = mOverlapSprite;
      }
      return true;
    }

    mIsOverlap = false;
    if (mIsOverlap != isCurrentOverlap)
    {
      mCurrentSprite = mSprite;
    }

    return false;
  }

  /**
   * @brief 
   * @param pos 
   * @return 
   */
  bool ImageButton::isClicked(sf::Vector2f pos)
  {
    return (mCurrentSprite.getGlobalBounds().contains(pos)) ? true : false;
  }

  /**
   * @brief Draw button's sprite on the screen
   * @param window Reference to sf::RenderWindow which draw button's sprite 
   */
  void ImageButton::render(sf::RenderWindow& window)
  {
    window.draw(mCurrentSprite);
  }
}