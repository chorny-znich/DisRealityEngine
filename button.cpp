#include "Button.h"

namespace dr
{
  Button::Button(sf::Vector2f size) :
    mPosition{ 0, 0 },
    mSize{ size },
    mOverlap{ false }
  {
    mArrowCursor->createFromSystem(sf::Cursor::Type::Arrow);
    mHandCursor->createFromSystem(sf::Cursor::Type::Hand);
  }

  void Button::setPosition(sf::Vector2f pos)
  {
    mPosition = pos;
  }
  sf::Vector2f Button::getPosition() const
  {
    return mPosition;
  }

  sf::Vector2f Button::getSize() const
  {
    return mSize;
  }
  void Button::update(sf::Time dt)
  {

  }
}