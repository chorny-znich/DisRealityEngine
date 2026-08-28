#pragma once
#include <cstdint>
#include <random>
#include <SFML/System/Vector2.hpp>

namespace dr
{
  namespace EngineUtility
  {
    int16_t getRandomInRange(int16_t min, int16_t max);
    uint16_t getMapID(sf::Vector2f pos);
  }
}