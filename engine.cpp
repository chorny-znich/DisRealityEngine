#include "engine.h"

namespace dr
{
  /**
  * @brief Default constructor.
  */
  Engine::Engine() :
    mVideoMode{1920, 1080},
    mWindow{mVideoMode, "DisReality Engine", sf::Style::Fullscreen}
  {
  }

  /**
   * @brief Game cycle
  */
  void Engine::run()
  {
    init();
    createStartScreen();
    while (mWindow.isOpen() && !mGameState.isEmpty()) {
      handleEvent();
      render();
    }
  }
}