#pragma once
#include <SFML/Graphics.hpp>

namespace dr
{
	/**
	 * @brief Abstract class for the game screens
	 */
	class Screen
	{
	public:
		virtual void init() = 0;
		virtual void handleInput() = 0;
		virtual void update() = 0;
		virtual void render(sf::RenderWindow& window) = 0;
	};
}