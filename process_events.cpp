#include "engine.h"

namespace dr
{
	/**
	 * @brief Process the system events like resizing a window, a mouse or keyboard clicking etc
	 */
	void Engine::processEvents()
	{
		while (const auto& event = mWindow.pollEvent())
		{
			event->visit([this](const auto& type) {
				this->handleEvent(type);
				if (!ScreenManager::isEmpty())
				{
					ScreenManager::getCurrent()->handleInput(type, mWindow);
				}
			});
		}
	}

	/**
   * @brief Close the window
   */
	void Engine::handleEvent(const sf::Event::Closed&)
	{
		mWindow.close();
	}
}