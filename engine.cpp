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
		while (isRunning())
		{
			const float dt = clock.restart().asSeconds();
			processEvents();
			update(dt);
			render();
		}
	}

	/**
	 * @brief Check if the game is still running using SFML
	 * @return if the game is still running
	 */
	bool Engine::isRunning() const
	{
		return false;
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
	}

	/**
	 * @brief Draw graphics on the screen
	 */
	void Engine::render()
	{
		mWindow.clear(sf::Color::White);
		mWindow.display();
	}
}
