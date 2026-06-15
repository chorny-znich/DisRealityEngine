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
    sf::Vector2f getSize() const;
    virtual void setPosition(sf::Vector2f pos) = 0;
    sf::Vector2f getPosition() const;
    
    virtual bool isOverlap(sf::Vector2f pos) = 0;
    virtual void render(sf::RenderWindow& window) = 0;

    /*void update(sf::Time dt);
    virtual bool isClicked(sf::Vector2f pos) = 0;
    */
  protected:
    sf::Vector2f mSize;
    sf::Vector2f mPosition;  
    /*
    std::optional<sf::Cursor> mArrowCursor;
    std::optional<sf::Cursor> mHandCursor;
    bool mOverlap;*/
  };
}