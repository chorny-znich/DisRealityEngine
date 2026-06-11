#pragma once
#include "screen_manager.h"
#include "engine_data.h"
#include <SFML/Graphics.hpp>

namespace dr
{
	/**
	 * @brief The game cycle managment.
	 * A game class that contains the game cycle must derive from this class and override virtual methods
	 */
	class Engine
	{
	public:
		Engine();
		Engine(Engine& engine) = delete;
		Engine& operator=(const Engine& engine) = delete;
		virtual ~Engine() = default;

		void run();
	protected:
		virtual void init();
	private:
		sf::VideoMode mVideoMode;
		sf::RenderWindow mWindow;

		EngineConfig mEngineConfig;
		WindowConfig mWindowConfig;

		bool isRunning() const;
		virtual void createStartScreen() = 0;
		void processEvents();
		void update(float dt);
		void render();

		void createWindow();
		std::pair<EngineConfig, WindowConfig> parseEngineConfig();
	};
}