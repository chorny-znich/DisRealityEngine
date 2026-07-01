#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace dr
{
  /**
     * @brief Base class for all dynamic, animate entities within the game world (players, NPCs, monsters).
     *
     * Combines sf::Drawable and sf::Transformable to leverage SFML 3's built-in
     * transformation matrices and rendering pipeline. Manages positioning, spatial states,
     * and visual sprite dispatching without enforcing specific gameplay mechanics.
     */
  class GameActor : public sf::Drawable, sf::Transformable
  {
  public:
    GameActor(const sf::Texture& texture, sf::IntRect rect);
    virtual ~GameActor() = default;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setVisibilityStatus(bool status);
  protected:
    sf::Sprite mSprite;
    bool mIsVisible;
  };
}
