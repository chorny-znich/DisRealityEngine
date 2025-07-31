#include "button.h"

namespace dr {
  Button::Button(sf::Vector2f size) :
    mPosition{ 0, 0 },
    mSize{ size }
  {
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
}