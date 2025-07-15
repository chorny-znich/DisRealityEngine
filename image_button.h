#pragma once
#include "button.h"

/**
 * @brief Button made from the image file
*/
namespace dr {
  class ImageButton : public Button
  {
  private:
    sf::Sprite mImage;

  public:
    ImageButton(sf::Vector2f size, const std::string& id);
    void setPosition(sf::Vector2f pos);
    virtual void render(sf::RenderWindow& window) override;
    virtual bool isClicked(sf::Vector2f pos) override;
  };
}