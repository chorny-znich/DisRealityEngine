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
    for (size_t i{ 0 }; i < mRenderedLines; i++)
    {
      sf::Text text = dr::TextManager::get(std::string(textStyle));
      text.setPosition({ mPosition.x, currentLinePos });
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
      size_t counter = 0;
      if (mLogStrings.size() <= mRenderedLines)
      {
        for (const auto& str : mLogStrings)
        {
          mRenderText[counter].setString(str);
          counter++;
        }
      }
      else
      {
        const auto iter = mLogStrings.begin() + HISTORY_SIZE - mRenderedLines;
        for (auto i = iter; i < mLogStrings.end(); i++)
        {
          mRenderText[counter].setString(*iter);
          counter++;
        }
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
    if (mLogStrings.size() > HISTORY_SIZE)
    {
      mLogStrings.pop_front();
    }
    mIsNeedUpdate = true;
  }
}