#pragma once
#include "entity.h"
#include "light_source.h"
#include <memory>

namespace dr
{
  /**
   * @brief 
   */
  class DecorationActor : public Entity
  {
  public:
    DecorationActor(uint16_t id, sf::IntRect rect, sf::Texture& texture);
    virtual void update(float dt) override;
    uint16_t getID() const;
    bool isLightSource() const;
    const LightSource* getLightSource() const;
    void initLight(float radius, sf::Color color);
  private:
    uint16_t mId;
    std::unique_ptr<LightSource> mLight{ nullptr };
  };
 
  using DecorationActorPtr = std::unique_ptr<DecorationActor>;
  using DecorationLayer = std::vector<std::unique_ptr<DecorationActor>>;
}