#include "text_button.h"

namespace dr
{
  TextButton::TextButton(sf::Vector2f size/*, sf::Text text, const std::string& str*/) :
    Button(size),
    mShape{ size },
    mColor{ sf::Color::Color(230, 231, 232) },
    mOverlapColor{ sf::Color(255, 160, 122) }
    /*   mText{ text },
    mString{ str },
    */
  {
    setPosition(mPosition);
    mShape.setFillColor(mColor);
    //mText.setString(mString);
  }
  
  /**
   * @brief set the position of the button
   * @param pos - sf::Vector2f from SFML3
   */
  void TextButton::setPosition(sf::Vector2f pos)
  {
    mShape.setPosition(pos);
    /*mText.setPosition({pos.x + ((mSize.x - mText.getLocalBounds().size.x) / 2),
    pos.y + ((mSize.y - mText.getLocalBounds().size.y) / 4) });*/
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
  /*
  void TextButton::setFillColor(sf::Color color)
  {
    mShape.setFillColor(color);
  }
  */
  /**
   * @brief 
   * @param window - sf::RenderWindow from SFML3 
   */
  void TextButton::render(sf::RenderWindow& window)
  {
    window.draw(mShape);
    //window.draw(mText);
  }

  /*
  bool TextButton::isClicked(sf::Vector2f pos)
  {
    return (mShape.getGlobalBounds().contains(pos)) ? true : false;
  }
  bool TextButton::isOverlap(sf::Vector2f pos)
  {
    return false;
  }*/
}