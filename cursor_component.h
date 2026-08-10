#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>

namespace dr
{
	enum class CursorMode
	{
		MOVE,
		EDIT
	};

	/**
	 * @brief Component for handling the rectangle cursor
	 */
	class CursorComponent
	{
	public:
		CursorComponent(sf::View& view);
		void init();
		void handleInput(sf::Vector2i mouseWindowPos, sf::RenderWindow& window);
		void update(float dt);
		void render(sf::RenderWindow& window);

		//GameData::MoveDirections getDirection(const sf::Vector2i& pos) const;
		sf::Vector2i getTilePosition() const;
		uint16_t getTileId() const;
		//sf::Vector2f getMousePosition() const;*/
		void setMapSize(sf::Vector2i size);
		//void setCursorMode(CursorMode mode);
		//CursorMode getCursorMode();
		void changeCursorColor(sf::Color color);
		void startEdit();
		void finishEdit();
	protected:
		sf::View& mGameView;
		sf::Vector2f mMousePosition;
		sf::Vector2i mTilePosition;
		uint16_t mTileId;
	private:
		const sf::Color DEFAULT_CURSOR_COLOR{ sf::Color::Black };
		const float CURSOR_WIDTH{ 3.f };
		float mTileSize{ 128.f };

		sf::Vector2i mMapSize;
		std::array<sf::RectangleShape, 4> mSquareCursor;
		CursorMode mCursorMode{ CursorMode::MOVE };
	};
}