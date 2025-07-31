#include "image_button.h"
#include "engine_data.h"

namespace dr {
  ImageButton::ImageButton(sf::Vector2f size, const std::string& id) :
    Button(size)
  {
    mImage.setTexture(Textures::get(id));
  }
  void ImageButton::setPosition(sf::Vector2f pos)
  {
    Button::setPosition(pos);
    mImage.setPosition(pos);
  }
  void ImageButton::render(sf::RenderWindow& window)
  {
    window.draw(mImage);
  }
  bool ImageButton::isClicked(sf::Vector2f pos)
  {
    return (mImage.getGlobalBounds().contains(pos)) ? true : false;
  }
}