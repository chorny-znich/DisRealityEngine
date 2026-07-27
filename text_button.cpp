#include "text_button.h"
#include "cursor_component.h"

namespace dr
{
  TextButton::TextButton(sf::Vector2f size, sf::Text text) :
    Button(size),
    mShape{ size },
    mColor{ sf::Color::Color(230, 231, 232) },
    mOverlapColor{ sf::Color(255, 160, 122) },
    mText{ text }
  {
    setPosition(mPosition);
    mShape.setFillColor(mColor);
  }
  
  /**
   * @brief set the position of the button
   * @param pos - sf::Vector2f from SFML3
   */
  void TextButton::setPosition(sf::Vector2f pos)
  {
    mShape.setPosition(pos);
    mText.setPosition({pos.x + ((mSize.x - mText.getLocalBounds().size.x) / 2),
    pos.y + ((mSize.y - mText.getLocalBounds().size.y) / 4) });
  }

  /**
   * @brief 
   * @param pos 
   * @return 
   */
  bool TextButton::isOverlap(sf::Vector2f pos)
  {
    if (mShape.getGlobalBounds().contains(pos))
    {
      mShape.setFillColor(mOverlapColor);
      return true;
    }
    else
    {
      mShape.setFillColor(mColor);
      return false;
    }
  }
  
  /**
   * @brief Check if the button overlap when clicked
   * @param pos - mouse cursor in world coordinates
   * @return 
   */
  bool TextButton::isClicked(sf::Vector2f pos)
  {
    return (mShape.getGlobalBounds().contains(pos)) ? true : false;
  }

  void TextButton::setFillColor(sf::Color color, sf::Color overlapColor)
  {
    mColor = color;
    mOverlapColor = overlapColor;
    mShape.setFillColor(color);
  }

  void TextButton::setString(sf::String str)
  {
      mString = str;
      mText.setString(mString);
  }
  
  /**
   * @brief 
   * @param window - sf::RenderWindow from SFML3 
   */
  void TextButton::render(sf::RenderWindow& window)
  {
    window.draw(mShape);
    window.draw(mText);
  }

  /**
   * @brief button get it's default color
   */
  void TextButton::clearOverlap()
  {
    mShape.setFillColor(mColor);
  }

  /*
  
  bool TextButton::isOverlap(sf::Vector2f pos)
  {
    return false;
  }*/
}