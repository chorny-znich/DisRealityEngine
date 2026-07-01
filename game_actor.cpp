#include "game_actor.h"
#include "SFML/Graphics/RenderTarget.hpp"

dr::GameActor::GameActor(const sf::Texture& texture, sf::IntRect rect) :
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
