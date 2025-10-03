#include "panel.h"
#include "image_button.h"
#include "text_button.h"

namespace dr
{
  Panel::Panel(sf::Vector2f size) :
    mPosition{ 0.f, 0.f },
    mSize{ size },
    mShape{ size }
  {
    mShape.setPosition(mPosition);
  }

  int Panel::handleInput(sf::Vector2f pos)
  {
    int index = -1;

    for (int i = 0; i < mButtons.size(); ++i)
    {
      if (mButtons[i]->isClicked({ pos.x, pos.y }))
      {
        index = i;
        break;
      }
    }
    return index;
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
    mButtons.push_back(imageButton);
    reorderButtons();
  }

  void Panel::addTextButton(sf::Vector2f size, sf::Text& text)
  {
    std::shared_ptr<TextButton> textButton = std::make_shared<TextButton>(size, text);
    mButtons.push_back(textButton);
    reorderButtons();
  }

  const std::vector<std::shared_ptr<Button>>& Panel::getButtons() const
  {
    return mButtons;
  }

  /**
   * @brief Change the order of buttons in the container
   */
  void Panel::reorderButtons()
  {
    const size_t CONTAINER_SIZE = mButtons.size();
    const int SHIFT = 15;
    // reorder the single button in the container
    if (CONTAINER_SIZE == 1) {
      mButtons[0]->setPosition({ mPosition.x + (mSize.x - mButtons[0]->getSize().x) / 2, 
        mPosition.y + (mSize.y - mButtons[0]->getSize().y) / 2});
    }
    // reorder buttons in the container with the even size
    else if (CONTAINER_SIZE % 2 == 0 && CONTAINER_SIZE != 1) {
      const float CENTER_POINT_PANEL = mPosition.y + mSize.y / 2;
      const int CENTER_POINT_POS = CONTAINER_SIZE / 2 - 1;
      // reorder buttons in the top half of the container
      for (int i{ CENTER_POINT_POS }; i >= 0; i--) {
        mButtons[i]->setPosition({ mPosition.x + (mSize.x - mButtons[0]->getSize().x) / 2,
        CENTER_POINT_PANEL - (SHIFT + mButtons[0]->getSize().y) * (CENTER_POINT_POS + 1 - i)});
      }
      // reorder buttons in the bottom half of the container
      for (int i{ CENTER_POINT_POS + 1 }; i < CONTAINER_SIZE; i++) {
        mButtons[i]->setPosition({ mPosition.x + (mSize.x - mButtons[0]->getSize().x) / 2,
        CENTER_POINT_PANEL + (SHIFT + mButtons[0]->getSize().y) * (i - (CENTER_POINT_POS + 1)) });
      }
    }
    else if (CONTAINER_SIZE % 2 != 0 && CONTAINER_SIZE != 1) {
      const float POS_X = mPosition.x;
      const float POS_Y = mPosition.y;
      const int CENTER_POINT_POS = CONTAINER_SIZE / 2;
      const float CENTER_POINT_PANEL = POS_Y + mSize.y / 2;
      const float CENTER_POINT_PANEL_TOP = CENTER_POINT_PANEL - (mButtons[CENTER_POINT_POS]->getSize().y / 2);
      const float CENTER_POINT_PANEL_BOTTOM = CENTER_POINT_PANEL + (mButtons[CENTER_POINT_POS]->getSize().y / 2);

      // reorder the button at the center of the container
      mButtons[CENTER_POINT_POS]->setPosition({ POS_X + (mSize.x - mButtons[CENTER_POINT_POS]->getSize().x) / 2,
        CENTER_POINT_PANEL_TOP });

      // reorder buttons in the top half of the container
      for (int i{ CENTER_POINT_POS - 1 }; i >= 0; i--) {
        mButtons[i]->setPosition({ mPosition.x + (mSize.x - mButtons[0]->getSize().x) / 2,
        CENTER_POINT_PANEL_TOP - (SHIFT + mButtons[0]->getSize().y) * (CENTER_POINT_POS - i) });
      }
      // reorder buttons in the bottom half of the container
      for (int i{ CENTER_POINT_POS + 1 }; i < CONTAINER_SIZE; i++) {
        mButtons[i]->setPosition({ mPosition.x + (mSize.x - mButtons[0]->getSize().x) / 2,
        CENTER_POINT_PANEL_BOTTOM + (SHIFT + (mButtons[0]->getSize().y) * (i - (CENTER_POINT_POS + 1))) });
      }
    }

    /*const size_t middleElement =
    for (auto& btn : mButtons) {

    }*/
  }
}