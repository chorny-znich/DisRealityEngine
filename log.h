#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>
#include <deque>
#include <string_view>

namespace dr
{
  /**
  * @brief Log the game information (game events, results of checking stats) on the screen
  */
  class Log
  {
  private:
    Log() = default;
  public:
    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;
    Log(Log&&) = delete;
    Log&& operator=(Log&&) = delete;

    static Log& instance()
    {
      static Log log;
      return log;
    }

    void init(sf::Vector2f panelSize, sf::Vector2f pos, std::string_view textStyle);
    void update();
    void render(sf::RenderWindow& window);

    void setPosition(sf::Vector2f pos);
    void addMessage(std::string_view msg);
  private:
    static constexpr sf::Color PANEL_BACKGROUND_COLOR{ 0, 0, 0, 225 };
    static constexpr float PANEL_OUTLINE_THICKNESS{ 5.f };
    static constexpr sf::Color PANEL_OUTLINE_COLOR{ 178, 34, 34, 250 };
    static constexpr float TEXT_HEIGHT{ 25.f };
    static constexpr float LEFT_PADDING{ 5.f };

    sf::RectangleShape mPanel;
    sf::Vector2f mPanelSize;
    sf::Vector2f mPosition;

    std::deque<std::string> mLogStrings;
    std::vector<sf::Text> mRenderText;
    
    uint8_t mRenderedLines{};
    bool mIsNeedUpdate{ false };
  };
}