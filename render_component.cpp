#include "render_component.h"
#include "engine_data.h"
#include <algorithm>

namespace dr
{
  void RenderComponent::updateFloorLayer(const sf::VertexArray& arr)
  {
    mFloorLayer = arr;
  }

  void RenderComponent::updateLevelLayer(LevelObjects& objs)
  {
    mLevelLayer = objs;
  }

  void RenderComponent::render(sf::RenderWindow& window)
  {
    window.draw(mFloorLayer, &(Textures::get("floor_texture")));
    for (const auto& ll : mLevelLayer) {
      window.draw(*ll);
    }
    /*for (const auto& sl : mStaticLayer) {
      window.draw(*sl);
    }*/
  }
}