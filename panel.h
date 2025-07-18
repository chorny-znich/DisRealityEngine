#pragma once
#include "button.h"
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

namespace dr
{
  /**
 * @brief The UI container that can contain UI elements such buttons
 */
  class Panel
  {
  public:
    Panel(sf::Vector2f size);
    void render(sf::RenderWindow& window);
    void setPosition(sf::Vector2f pos);
    void setColor(sf::Color color);

    void addButton(std::shared_ptr<Button> btn);
  private:
    sf::Vector2f mPosition;
    sf::Vector2f mSize;
    sf::RectangleShape mShape;
    sf::Color mColor;

    std::vector<std::shared_ptr<Button>> mButtons;
  };
}