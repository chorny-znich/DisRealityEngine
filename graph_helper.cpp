#include "graph_helper.h"

namespace dr
{
  namespace GraphHelper
  {
    sf::Image getLightImage()
    {
      sf::Image image;
      image.resize({ 256, 256 }, sf::Color::Transparent);
      sf::Vector2i center{ 128, 128 };
      for (unsigned int y{ 0 }; y < 256; y++)
      {
        for (unsigned int x{ 0 }; x < 256; x++)
        {
          int dx = static_cast<int>(x) - center.x;
          int dy = static_cast<int>(y) - center.y;
          float distance = std::sqrtf(dx * dx + dy * dy);
          if (distance <= 128.f)
          {
            uint8_t alpha = static_cast<uint8_t>((distance / 128.f) * 235.f);
            image.setPixel({ x, y }, { 15, 15, 25, alpha });
          }
        }
      }
      return image;
    }
  }
}