#pragma once
#include "screen.h"
#include <string>
#include <unordered_map>
#include <memory>
#include "game_state.h"

namespace dr
{
/**
 * @brief manage game's screens
 */
  class ScreenManager
  {
  private:
    std::unordered_map <std::string, std::shared_ptr<Screen>> mScreens;
  public:
    ScreenManager() = delete;
    template <typename ScreenPointer>
    static void createScreen(std::string screenId)
    {
      std::shared_ptr<ScreenPointer> pScreen = std::make_shared<ScreenPointer>();
      pScreen->init();
      GameState::addScreen(std::move(pScreen));
    }
  };
}