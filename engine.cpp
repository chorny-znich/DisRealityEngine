#include "engine.h"
#include "text_manager.h"
#include "string_manager.h"
#include "cursor_manager.h"
#include "ini_parser.h"
#include <iostream>

namespace dr
{
	/**
	 * @brief Default constructor.
	 */
	dr::Engine::Engine()
	{
		auto config = parseEngineConfig();
		mEngineConfig = config.first;
		mWindowConfig = config.second;
		createWindow();
	}

	/**
	 * @brief Game cycle
	 */
	void Engine::run()
	{
		sf::Clock clock;
		init();
		createStartScreen();
		while (isRunning())
		{
			const float dt = clock.restart().asSeconds();
			processEvents();
			update(dt);
			render();
		}
	}

	/**
	 * @brief Check if the game is still running using SFML and check if there are any active screens in the stack
	 * @return if the game is still running
	 */
	bool Engine::isRunning() const
	{
		return mWindow.isOpen() && !ScreenManager::isEmpty();
	}

	/**
	 * @brief Initialize resources
	 */
	void Engine::init()
	{
		// load managers
		try
		{
			Textures::init(path::TextureList.data());
			Fonts::init(path::FontsList.data());
			TextManager::init(path::TextStyle.data());
			StringManager::init(path::Strings.data());
			CursorManager::init();
		}
		catch (const std::runtime_error& err)
		{
			std::cout << err.what() << std::endl;
		}
	}

	/**
	 * @brief Update game's logic
	 */
	void Engine::update(float dt)
	{
		if (!ScreenManager::isEmpty())
		{
			ScreenManager::getCurrent()->update(dt);
		}
	}

	/**
	 * @brief Draw graphics on the screen
	 */
	void Engine::render()
	{
		mWindow.clear(sf::Color::White);
		if (!ScreenManager::isEmpty())
		{
			ScreenManager::getCurrent()->render(mWindow);
		}
		mWindow.display();
	}

	/**
	 * @brief Create a window according settings from the ini file
	 */
	void Engine::createWindow()
	{
		mVideoMode = mWindowConfig.mResolutionState == ResolutionState::NATIVE ?
			sf::VideoMode::getDesktopMode() :
			sf::VideoMode({ mWindowConfig.mResolution.x, mWindowConfig.mResolution.y });
		sf::State windowState = mWindowConfig.mWindowMode == WindowMode::WINDOW ?
			sf::State::Windowed : sf::State::Fullscreen;
		mWindow.create(mVideoMode, mEngineConfig.mTitle, sf::Style::Default, windowState);
	}

	/**
	 * @brief read the engine configuration settings from the file. The file must be at the 'config/engine_config.ini' path.
	 * @return EngineConfig structure which contains engine settings and WindowConfig structure which contains window settings
	*/
	std::pair<EngineConfig, WindowConfig> Engine::parseEngineConfig()
	{
		EngineConfig engineConfig;
		dr::IniDocument doc = dr::loadIniDocument(path::EngineConfigFile.data());

			dr::Section generalSection = doc.getSection("general");
			try 
			{
				engineConfig.mTitle = generalSection.at("title");
			}
			catch (const std::exception& e) 
			{
				std::cerr <<
					std::format("Error in [general] section: {}\n", e.what());
			}

			WindowConfig windowConfig;
			dr::Section windowSection = doc.getSection("window");
			try 
			{
				windowConfig.mResolutionState = (windowSection.at("resolution_state") == "NATIVE") ?
					ResolutionState::NATIVE : ResolutionState::CUSTOM;
				windowConfig.mResolution.x = std::stoi(windowSection.at("resolution_x"));
				windowConfig.mResolution.y = std::stoi(windowSection.at("resolution_y"));
				windowConfig.mWindowMode = (windowSection.at("window_mode") == "WINDOW") ?
					WindowMode::WINDOW : WindowMode::FULLSCREEN;
			}
			catch (const std::exception& e) 
			{
				std::cerr <<
					std::format("Error in [window] section {}\n", e.what());
			}

			return { engineConfig, windowConfig };
	}
}
