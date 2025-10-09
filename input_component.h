#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "engine_data.h"

/**
 * @brief Component for handling user's input
*/
namespace dr
{
	class InputComponent
	{
	private:
		const float TILE_SIZE = 128.f;
		
		sf::View& mGameView;
		sf::Vector2i mMapSize;
		sf::Vector2f mMousePosition;
		sf::Vector2i mTilePosition;
		std::array<sf::RectangleShape, 4> mSquareCursor;
		CursorMode mCursorMode{ CursorMode::MOVE };
		
	public:
		InputComponent(sf::View& view);
		void inputHandler(sf::Vector2i position, sf::RenderWindow* window);
		void inputHandler(sf::Mouse::Button button, bool isPressed, sf::Vector2i position, sf::RenderWindow* window);
		void update(sf::Time dt);
		void render(sf::RenderWindow& window);

		//GameData::MoveDirections getDirection(const sf::Vector2i& pos) const;
		sf::Vector2i getTilePosition() const;
		//sf::Vector2f getMousePosition() const;*/
		void setMapSize(sf::Vector2i size);
		void setCursorMode(CursorMode mode);
		CursorMode getCursorMode();
		void changeCursorColor(sf::Color color);
		void finishEditMode();
	};
}