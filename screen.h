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
		virtual ~Screen() = default;

		virtual void init() = 0;
		virtual void handleInput(const sf::Event& event) {};
		virtual void update(float dt) = 0;
		virtual void render(sf::RenderWindow& window) = 0;
	};
}