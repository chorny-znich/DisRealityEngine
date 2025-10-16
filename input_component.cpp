#include "input_component.h"
#include "imgui/imgui.h"
#include <string>
#include <format>

namespace dr
{
    InputComponent::InputComponent(sf::View& view) :
        mGameView{ view },
        mMousePosition{ 0, 0 },
        mTilePosition{ 0, 0 },
        mSquareCursor{
        sf::RectangleShape{{128.f, 3.f}},
        sf::RectangleShape{{3.f, 128.f}},
        sf::RectangleShape{{128.f, 3.f}},
        sf::RectangleShape{{3.f, 128.f}}
        }
    {
        changeCursorColor(sf::Color::Black);
    }

    void InputComponent::changeCursorColor(sf::Color color)
    {
        for (auto& elem : mSquareCursor) {
            elem.setFillColor(color);
        }
    }
   
    void InputComponent::finishEditMode()
    {
        mCursorMode = CursorMode::MOVE;
        changeCursorColor(sf::Color::Black);
        mMousePosition.x = mTilePosition.x * TILE_SIZE;
        mMousePosition.y = mTilePosition.y * TILE_SIZE;
    }
    
    void InputComponent::inputHandler(sf::Vector2i position, sf::RenderWindow* window)
    {
        if (mCursorMode == CursorMode::MOVE) {
            mMousePosition = window->mapPixelToCoords(position, mGameView);
            mTilePosition = { static_cast<int>(mMousePosition.x) / 128, static_cast<int>(mMousePosition.y / 128) };
        }
    }

    void InputComponent::inputHandler(sf::Mouse::Button button, bool isPressed, sf::Vector2i position, sf::RenderWindow* window)
    {
      mMousePosition = window->mapPixelToCoords(position, mGameView);
      mTilePosition = { static_cast<int>(mMousePosition.x) / 128, static_cast<int>(mMousePosition.y / 128) };
      /*if (mPlayerNear && !mPlayerMove) {
        mPlayerMove = true;
      }*/
        if (button == sf::Mouse::Right && mCursorMode == CursorMode::MOVE) {
            mCursorMode = CursorMode::EDIT;
            changeCursorColor(sf::Color::Red);
        }
    }
    
    void InputComponent::update(sf::Time dt)
    {
        // Limit the cursor to the map area
        if (mTilePosition.x >= mMapSize.x) {
            mTilePosition.x = mMapSize.x;
            mMousePosition.x = mTilePosition.x * TILE_SIZE - TILE_SIZE;
        }
        if (mTilePosition.x <= 0) {
            mTilePosition.x = 0;
            mMousePosition.x = 0;
        }
        if (mTilePosition.y >= mMapSize.y) {
            mTilePosition.y = mMapSize.y;
            mMousePosition.y = mTilePosition.y * TILE_SIZE - TILE_SIZE;
        }
        if (mTilePosition.y <= 0) {
            mTilePosition.y = 0;
            mMousePosition.y = 0;
        }

        // Update the cursor position
        sf::Vector2i tileCoords = { static_cast<int>(mMousePosition.x) / 128, static_cast<int>(mMousePosition.y / 128) };
        mSquareCursor[0].setPosition(tileCoords.x * TILE_SIZE, tileCoords.y * TILE_SIZE);
        mSquareCursor[1].setPosition(tileCoords.x * TILE_SIZE, tileCoords.y * TILE_SIZE);
        mSquareCursor[2].setPosition(tileCoords.x * TILE_SIZE, tileCoords.y * TILE_SIZE + TILE_SIZE);
        mSquareCursor[3].setPosition(tileCoords.x * TILE_SIZE + TILE_SIZE - 3.f, tileCoords.y * TILE_SIZE);
        mTilePosition = { tileCoords.x, tileCoords.y };
        
        ImGui::Begin("Input component");
        ImGui::Text(std::format("Current map size: x:{},y:{}", mMapSize.x, mMapSize.y).c_str());
        ImGui::Text(std::format("Mouse position: x:{},y:{}", mMousePosition.x, mMousePosition.y).c_str());
        ImGui::Text(std::format("Tile position: x:{},y:{}", mTilePosition.x, mTilePosition.y).c_str());
        ImGui::End();
    }
    
    void InputComponent::render(sf::RenderWindow& window)
    {
        for (const auto& item : mSquareCursor) {
            window.draw(item);
        }
    }
    /*
    GameData::MoveDirections InputComponent::getDirection(const sf::Vector2i& pos) const
    {/*
        GameData::MoveDirections result = GameData::MoveDirections::NONE;*/
        /* if (mTilePosition.x == pos.x) {
          if (mTilePosition.y - pos.y == 1) {
            result = GameData::MoveDirections::DOWN;
          }
          else if (mTilePosition.y - pos.y == -1) {
            result = GameData::MoveDirections::UP;
          }
        }
        else if (mTilePosition.y == pos.y) {
          if (mTilePosition.x - pos.x == 1) {
            result = GameData::MoveDirections::RIGHT;
          }
          else if (mTilePosition.x - pos.x == -1) {
            result = GameData::MoveDirections::LEFT;
          }
        }*//*
        return result;
    }
    */
    sf::Vector2i InputComponent::getTilePosition() const
    {
        return mTilePosition;
    }
    /*
    sf::Vector2f InputComponent::getMousePosition() const
    {
        return mMousePosition;
    }
    */
    void InputComponent::setMapSize(sf::Vector2i size)
    {
        mMapSize = size;
    }
    void InputComponent::setCursorMode(CursorMode mode)
    {
        mCursorMode = mode;
    }
    dr::CursorMode InputComponent::getCursorMode()
    {
        return mCursorMode;
    }
}