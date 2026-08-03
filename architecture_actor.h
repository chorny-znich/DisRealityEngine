#pragma once
#include "game_actor.h"

namespace dr
{
  /**
    * @brief Abstract base class representing static architectural map elements like walls and corners.
    *
    * Inherits from dr::GameActor to integrate seamlessly with the SFML 3 rendering pipeline.
    * Enforces unique identification for every map asset via a tracking ID.
    */
  class ArchitectureActor : public GameActor
  {
  public:
    ArchitectureActor(uint16_t id, sf::IntRect rect, sf::Texture& texture);
    virtual void update(float dt) override;
    uint16_t getID() const;
  private:
    uint16_t mId;
  };
  using ArchitectureActorPtr = std::unique_ptr<ArchitectureActor>;
  using ArchitectureLayer = std::vector<std::unique_ptr<ArchitectureActor>>;
}