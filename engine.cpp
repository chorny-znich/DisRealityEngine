#include "engine.h"
#include <format>

namespace dr
{
  /**
  * @brief Default constructor. Read the engine's configuration from the ini file.
  */
  Engine::Engine()
  {
    mDatabase.init();
    auto p = parseEngineConfig();
    mEngineConfig = p.first;
    mWindowConfig = p.second;
    createWindow();
  }

  /**
   * @brief Game cycle
  */
  void Engine::run()
  {
    sf::Clock clock;
    init();
    ImGui::SFML::Init(mWindow);
    createStartScreen();
    while (mWindow.isOpen() && !mGameState.isEmpty()) {
      sf::Time dt = clock.restart();
      handleEvent();
      update(dt);
      render();
    }
    ImGui::SFML::Shutdown();
  }

  /**
   * @brief Create a window with settings from the ini file
  */
  void Engine::createWindow()
  {
    mVideoMode = mWindowConfig.mResolutionState == ResolutionState::NATIVE ?
      sf::VideoMode::getDesktopMode() :
      sf::VideoMode(mWindowConfig.mResolution.x, mWindowConfig.mResolution.y);
    mWindow.create(mVideoMode, mEngineConfig.mTitle, mWindowConfig.mWindowMode == WindowMode::WINDOW ?
      sf::Style::Default : sf::Style::Fullscreen);
  }

  /**
   * @brief read the engine configuration settings from the file. The file must be at the 'config/engine_config.ini' path.
   * @return EngineConfig structure which contains engine settings and WindowConfig structure which contains window settings
  */
  std::pair<EngineConfig, WindowConfig> Engine::parseEngineConfig()
  {
    EngineConfig engineConfig;
    dr::IniDocument doc = dr::loadIniDocument(path::EngineConfigFile);

    dr::Section generalSection = doc.getSection("general");
    try {
      engineConfig.mTitle = generalSection.at("title");
    }
    catch (...) {
      std::cerr <<
        std::format("Error while reading data from the general section of the configuration file\n");
    }

    WindowConfig windowConfig;
    dr::Section windowSection = doc.getSection("window");
    try {
      windowConfig.mResolutionState = (windowSection.at("resolution_state") == "NATIVE") ?
        ResolutionState::NATIVE : ResolutionState::CUSTOM;
      windowConfig.mResolution.x = std::stoi(windowSection.at("resolution_x"));
      windowConfig.mResolution.y = std::stoi(windowSection.at("resolution_y"));
      windowConfig.mWindowMode = (windowSection.at("window_mode") == "WINDOW") ?
        WindowMode::WINDOW : WindowMode::FULLSCREEN;
    }
    catch (...) {
      std::cerr <<
        std::format("Error while reading data from the window section of the configuration file\n");
    }

    return { engineConfig, windowConfig };
  }
}