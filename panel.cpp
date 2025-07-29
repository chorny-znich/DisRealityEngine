#include "panel.h"
#include "image_button.h"

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

  void Panel::addImageButton(sf::Vector2f size, std::string textureId)
  {
    std::shared_ptr<ImageButton> imageButton = std::make_shared<ImageButton>(size, textureId);
    imageButton->setPosition({ mPosition.x + (mSize.x - size.x) / 2, mPosition.y + (mSize.y - size.y) / 2 });
    mButtons.push_back(imageButton);
  }
}