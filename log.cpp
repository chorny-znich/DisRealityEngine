#include "log.h"
#include "text_manager.h"

namespace dr
{
  /**
   * @brief 
   */
  void Log::init(sf::Vector2f panelSize, sf::Vector2f pos, std::string_view textStyle)
  {
    mPanelSize = panelSize;
    mPanel.setSize(mPanelSize);
    setPosition(pos);
    mPanel.setFillColor(PANEL_BACKGROUND_COLOR);
    mPanel.setOutlineThickness(PANEL_OUTLINE_THICKNESS);
    mPanel.setOutlineColor(PANEL_OUTLINE_COLOR);

    mRenderedLines = static_cast<uint8_t>(mPanelSize.y / TEXT_HEIGHT);
    mRenderText.reserve(mRenderedLines);
    float currentLinePos = mPosition.y;
    const std::string style{ std::string(textStyle) };
    for (size_t i{ 0 }; i < mRenderedLines; i++)
    {
      sf::Text text = dr::TextManager::get(style);
      text.setPosition({ mPosition.x + LEFT_PADDING, currentLinePos });
      mRenderText.push_back(std::move(text));
      currentLinePos += TEXT_HEIGHT;
    }
  }

  /**
   * @brief 
   */
  void Log::update()
  {
    if (mIsNeedUpdate)
    {
      size_t counter = mRenderedLines - 1;
      for (const auto& str : mLogStrings)
      {
        if (mLogStrings.size() == mRenderedLines)
        {
          mRenderText[counter].setString(str);
        }
        else
        {
          mRenderText[counter - (mRenderedLines - mLogStrings.size())].setString(str);
        }
        
        counter--;
      }
      mIsNeedUpdate = false;
    }
  }

  void Log::render(sf::RenderWindow& window)
  {
    window.draw(mPanel);
    for (const auto& text : mRenderText)
    {
      window.draw(text);
    }
  }

  /**
   * @brief
   * @param pos Position on the screen
   */
  void Log::setPosition(sf::Vector2f pos)
  {
    mPosition = pos;
    mPanel.setPosition(pos);
  }

  /**
   * @brief 
   * @param msg 
   */
  void Log::addMessage(std::string_view msg)
  {
    mLogStrings.emplace_back(msg);
    if (mLogStrings.size() > mRenderedLines)
    {
      mLogStrings.pop_front();
    }
    mIsNeedUpdate = true;
  }
}