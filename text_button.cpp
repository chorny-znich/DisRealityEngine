#include "text_button.h"

namespace dr {
  TextButton::TextButton(sf::Vector2f size, sf::Text& text) :
    Button(size),
    mText{ text },
    mShape{ size },
    mColor{ sf::Color::Color(230, 231, 232) }
  {
    mShape.setFillColor(mColor);
    setPosition(mPosition);
  }

  void TextButton::setPosition(sf::Vector2f pos)
  {
    mShape.setPosition(pos);
    mText.setPosition({ pos.x + ((mSize.x - mText.getLocalBounds().width) / 2),
    pos.y + ((mSize.y - mText.getLocalBounds().height) / 4) });
  }

  void TextButton::setFillColor(sf::Color color)
  {
    mShape.setFillColor(color);
  }

  void TextButton::render(sf::RenderWindow& window)
  {
    window.draw(mShape);
    window.draw(mText);
  }
  bool TextButton::isClicked(sf::Vector2f pos)
  {
    return (mShape.getGlobalBounds().contains(pos)) ? true : false;
  }
}