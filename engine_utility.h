#pragma once
#include <cstdint>
#include <random>
#include <SFML/System/Vector2.hpp>

namespace dr
{
  namespace EngineUtility
  {
    [[nodiscard]] std::int16_t getRandomInRange(std::int16_t min, std::int16_t max);
  }
}