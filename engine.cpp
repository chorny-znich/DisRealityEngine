#include "engine.h"

namespace dr
{
	/**
	 * @brief Default constructor.
	 */
	dr::Engine::Engine() :
		mVideoMode({800, 600}),
		mWindow(mVideoMode, "DisRealityEngine")
	{
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
	 * @brief Process the system events like resizing a window, a mouse or keyboard clicking etc
	 */
	void Engine::processEvents()
	{
		while (const auto& events = mWindow.pollEvent())
		{
			if (events->is<sf::Event::Closed>())
			{
				mWindow.close();
			}
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
}
