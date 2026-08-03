#include "game_actor.h"
#include "SFML/Graphics/RenderTarget.hpp"

dr::GameActor::GameActor(sf::Sprite sprite) :
  mSprite(std::move(sprite)),
  mIsVisible{true}
{
}

/**
 * @brief 
 * @param rect 
 * @param texture 
 */
dr::GameActor::GameActor(sf::IntRect rect, const sf::Texture& texture) :
  mSprite(texture),
  mIsVisible{true}
{
  mSprite.setTextureRect(rect);
}

void dr::GameActor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if (mIsVisible)
  {
    states.transform *= getTransform();
    target.draw(mSprite, states);
  }
}

void dr::GameActor::setVisibilityStatus(bool status)
{
  mIsVisible = status;
}