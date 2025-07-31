#include "engine.h"

namespace dr
{
	void Engine::handleInput(sf::Mouse::Button button, bool isPressed, sf::Vector2i position, sf::RenderWindow* window)
	{
		if (!mGameState.isEmpty()) {
			mGameState.getCurrent()->inputHandler(button, isPressed, position, window);
		}
	}
}