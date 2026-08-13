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
    sf::Vector2f position{ 0.f, 0.f };
    float radius{ 128.f };
    sf::Color color{ sf::Color::White };
    float intensity{ 1.0f };
  };
}