#include "decoration_actor.h"

namespace dr
{
  DecorationActor::DecorationActor(uint16_t id, sf::IntRect rect, sf::Texture& texture) :
    GameActor(rect, texture),
    mId{ id }
  {
  }

  /**
   * @brief Method is empty because the architecture actor is static map element
   * @param dt delta time
   */
  void DecorationActor::update(float dt)
  {
  }

  uint16_t DecorationActor::getID() const
  {
    return mId;
  }
}