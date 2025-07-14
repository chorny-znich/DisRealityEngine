#include "engine.h"

namespace dr
{
	/**
	* @brief Handle system events. Close the game.
	*/
	void Engine::handleEvent()
	{
		sf::Event event;
		while (mWindow.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				mWindow.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape) {
					mWindow.close();
				}
				break;
			}
		}
	}
}