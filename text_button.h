#pragma once
#include "button.h"
#include <SFML/System/String.hpp>

namespace dr
{
  class TextButton : public Button
  {
  public:
    TextButton(sf::Vector2f size, sf::Text text);
    void setPosition(sf::Vector2f pos) override;
    void setFillColor(sf::Color color, sf::Color overlapColor);
    void setString(sf::String str);
    
    virtual bool isOverlap(sf::Vector2f pos) override;
    virtual bool isClicked(sf::Vector2f pos) override;
    virtual void render(sf::RenderWindow& window) override;

    void clearOverlap();
  private:
    sf::RectangleShape mShape;
    sf::Color mColor;
    sf::Color mOverlapColor;
    sf::Text mText;
    sf::String mString;
  };
}