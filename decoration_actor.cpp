#include "decoration_actor.h"

namespace dr
{
  DecorationActor::DecorationActor(uint16_t id, sf::IntRect rect, sf::Texture& texture) :
    Entity(rect, texture),
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

  /**
   * @brief 
   * @return 
   */
  bool DecorationActor::isLightSource() const
  {
      return mLight != nullptr;
  }

  /**
   * @brief 
   * @return get raw pointer to the LightSource structure
   */
  const LightSource* DecorationActor::getLightSource() const
  {
    return mLight.get();
  }

  /**
   * @brief 
   * @param radius 
   * @param color 
   */
  void DecorationActor::initLight(float radius, sf::Color color)
  {
    mLight = std::make_unique<LightSource>();
    mLight->radius = radius;
    mLight->color = color;
  }
}