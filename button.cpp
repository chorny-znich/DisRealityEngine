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
}