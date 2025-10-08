#pragma once
#include "asset_manager.h"
#include "engine_data.h"
#include "game_state.h"
#include "text_manager.h"
#include "database.h"
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

namespace dr
{
	/**
	 * @brief The game cycle managment.
	 * A game class that contains the game cycle must derive this class and override virtual methods.
	 */
	class Engine
	{
	private:
		sf::VideoMode mVideoMode;
		sf::RenderWindow mWindow;

		EngineConfig mEngineConfig;
		WindowConfig mWindowConfig;

		GameState mGameState;

		void handleEvent();
		void handleInput(sf::Mouse::Button button, bool isPressed, sf::Vector2i position, sf::RenderWindow* window);
		void update(sf::Time dt);
		void render();

		void createWindow();
		std::pair<EngineConfig, WindowConfig> parseEngineConfig();
	protected:
		Textures mTextureManager;
		Sounds mSoundManager;
		Fonts mFontManager;
		TextManager mTextManager;
		Database mDatabase;

		virtual void createStartScreen() = 0;
		virtual void init() = 0;
	public:
		Engine();
		Engine(Engine& engine) = delete;
		Engine& operator=(const Engine& engine) = delete;

		void run();
	};
}