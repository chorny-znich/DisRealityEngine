#pragma once

#include <SFML/Graphics.hpp>

/**
 * @brief Base class for the UI element - button
*/
namespace dr {
  enum class ButtonTypes
  {
    TEXT,
    IMAGE
  };

  class Button
  {
  protected:
    sf::Vector2f mPosition;
    sf::Vector2f mSize;
    
  public:
    Button(sf::Vector2f size);
    void setPosition(sf::Vector2f pos);
    virtual void render(sf::RenderWindow& window) = 0;
    virtual bool isClicked(sf::Vector2f pos) = 0;
  };
}