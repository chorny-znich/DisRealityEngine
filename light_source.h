#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

namespace dr
{
  /**
   * @brief Data for creating effects from light sources 
   */
  struct LightSource
  {
    float radius{ 128.f };
    sf::Color color{ sf::Color::White };
    float intensity{ 1.0f };
  };
}