#pragma once
#include <cstdint>
#include <random>
#include <SFML/System/Vector2.hpp>

namespace dr
{
  namespace EngineUtility
  {
    [[nodiscard]] std::int16_t getRandomInRange(std::int16_t min, std::int16_t max);
    [[nodiscard]] std::uint16_t getTileID(sf::Vector2f pos, std::int16_t mapWidth);
  }
}