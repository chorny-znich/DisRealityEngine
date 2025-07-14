#pragma once
#include "screen.h"
#include <memory>
#include <stack>

namespace dr
{
  /**
   * @brief Game state management
  */
  class GameState
  {
  private:
    std::stack<std::shared_ptr<Screen>> mScreens;

    static GameState* mpState;

  public:
    GameState();

    static void addScreen(std::shared_ptr<Screen> pScreen);
    static void destroyScreen();

    std::shared_ptr<Screen> getCurrent();
    bool isEmpty() const;
  };
}