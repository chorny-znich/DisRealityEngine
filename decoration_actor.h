#pragma once
#include "game_actor.h"

namespace dr
{
  /**
   * @brief 
   */
  class DecorationActor : public GameActor
  {
  public:
    DecorationActor(uint16_t id, sf::IntRect rect, sf::Texture& texture);
    virtual void update(float dt) override;
    uint16_t getID() const;
  private:
    uint16_t mId;
  };
 
  using DecorationActorPtr = std::unique_ptr<DecorationActor>;
  using DecorationLayer = std::vector<std::unique_ptr<DecorationActor>>;
}