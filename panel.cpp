#include "panel.h"

namespace dr
{
  Panel::Panel(sf::Vector2f size) :
    mPosition{ 0.f, 0.f },
    mSize{ size },
    mShape{ size }
  {
    mShape.setPosition(mPosition);
  }

  void Panel::render(sf::RenderWindow& window)
  {
    window.draw(mShape);
    for (const auto& btn : mButtons) {
      btn->render(window);
    }
  }

  void Panel::setPosition(sf::Vector2f pos)
  {
    mPosition = pos;
    mShape.setPosition(mPosition);
  }

  void Panel::setColor(sf::Color color)
  {
    mShape.setFillColor(color);
  }

  void Panel::addButton(std::shared_ptr<Button> btn)
  {
    btn->setPosition({ mPosition.x + 10, mPosition.y + 10 });
    mButtons.push_back(btn);
  }
}