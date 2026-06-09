#pragma once
#include "screen_manager.h"
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
		ScreenManager mScreenManager;
	private:
		sf::VideoMode mVideoMode;
		sf::RenderWindow mWindow;

		bool isRunning() const;
		virtual void init() = 0;
		virtual void createStartScreen() = 0;
		void processEvents();
		void update(float dt);
		void render();
	};
}