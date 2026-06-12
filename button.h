#pragma once
#include <SFML/Graphics.hpp>

namespace dr
{
  /**
   * @brief Types of the buttons
   */
  enum class ButtonTypes
  {
    TEXT,
    IMAGE
  };

  /**
   * @brief Base class for the UI element - button
   */
  class Button
  {
  public:
    Button(sf::Vector2f size);
    virtual void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
    void update(sf::Time dt);
    virtual void render(sf::RenderWindow& window) = 0;
    virtual bool isClicked(sf::Vector2f pos) = 0;
    virtual bool isOverlap(sf::Vector2f pos) = 0;
  protected:
    sf::Vector2f mPosition;
    sf::Vector2f mSize;

    std::optional<sf::Cursor> mArrowCursor;
    std::optional<sf::Cursor> mHandCursor;
    bool mOverlap;
  };
}