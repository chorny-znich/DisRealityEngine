#pragma once
#include "button.h"

/**
 * @brief Button made from a rectangle and an inner text 
*/
namespace dr {
  class TextButton : public Button
  {
  private:
    sf::Text& mText;
    sf::RectangleShape mShape;
    sf::Color mColor;

  public:
    TextButton(sf::Vector2f size, sf::Text& text);
    void setPosition(sf::Vector2f pos);
    void setFillColor(sf::Color color);
    virtual void render(sf::RenderWindow& window) override;

    virtual bool isClicked(sf::Vector2f pos) override;
  };
}