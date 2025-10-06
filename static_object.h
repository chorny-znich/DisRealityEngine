#pragma once
#include <SFML/Graphics.hpp>

namespace dr
{
  /**
   * @brief A base class for all objects that don't move but can have the animation
  */
  class StaticObject : public sf::Drawable
  {
  private:
      size_t mId;
  protected:
    sf::Sprite mSprite;
  public:
    StaticObject(sf::Sprite sprite);
    void setId(size_t id);
    size_t getId() const;
    virtual void update(sf::Time dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  };
}