#pragma once
#include "button.h"

namespace dr
{
  class TextButton : public Button
  {
  public:
    TextButton(sf::Vector2f size, sf::Text text, const std::string& str);
    void setPosition(sf::Vector2f pos);
    void setFillColor(sf::Color color);
    virtual void render(sf::RenderWindow& window) override;

    virtual bool isClicked(sf::Vector2f pos) override;
    virtual bool isOverlap(sf::Vector2f pos) override;
  private:
    sf::Text mText;
    std::string mString;
    sf::RectangleShape mShape;
    sf::Color mColor;
  };
}