#pragma once

#include <SFML/Graphics.hpp>

namespace dr {
  /**
   * @brief Abstract class for game screens
  */
  class Screen {
  public:
    virtual void init() = 0;
    virtual void inputHandler(sf::Keyboard::Key key, bool isPressed) = 0;
    virtual void inputHandler(sf::Mouse::Button button, bool isPressed, sf::Vector2i position, sf::RenderWindow* window) = 0;
    virtual void update(sf::Time dt) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
  };
}