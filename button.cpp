#include "Button.h"

namespace dr
{
  Button::Button(sf::Vector2f size) :
 //   mPosition{ 0, 0 },
    mSize{ size }//,
 //   mOverlap{ false }
  {
   /* mArrowCursor->createFromSystem(sf::Cursor::Type::Arrow);
    mHandCursor->createFromSystem(sf::Cursor::Type::Hand);*/
  }

  /**
   * @brief 
   * @return size of the button as sf::Vector2f 
   */
  sf::Vector2f Button::getSize() const
  {
    return mSize;
  }
  
  /**
   * @brief 
   * @return 
   */
  sf::Vector2f Button::getPosition() const
  {
    return mPosition;
  }

  /*
  void Button::update(sf::Time dt)
  {

  }*/
}