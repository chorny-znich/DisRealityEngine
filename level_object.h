#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace dr
{
  /**
    * @brief Abstract base class representing static architectural map elements like walls and corners.
    *
    * Inherits from sf::Drawable to integrate seamlessly with the SFML 3 rendering pipeline.
    * Enforces unique identification for every map asset via a tracking ID.
    */
  class LevelObject : public sf::Drawable
  {
  public:
    LevelObject(uint16_t id, sf::IntRect rect, sf::Texture& texture);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setPosition(sf::Vector2f pos);
    uint16_t getID() const;
  private:
    uint16_t mId;
    sf::Sprite mSprite;
  };
  using LevelObjectPtr = std::shared_ptr<LevelObject>;
  using LevelObjects = std::vector<std::shared_ptr<LevelObject>>;
}