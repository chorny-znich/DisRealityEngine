#include "engine.h"

namespace dr
{
  /**
   * @brief Render the graphics from the current active screen
  */
  void Engine::render()
  {
    if (!mGameState.isEmpty()) {
      mWindow.clear(sf::Color::White);
      //ImGui::SFML::Render(mWindow);
      mGameState.getCurrent()->render(mWindow);
      mWindow.display();
    }
  }
}