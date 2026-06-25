#pragma once
#include <SFML\Graphics\Text.hpp>

namespace dr
{
  namespace UIHelper
  {
    /**
     * @brief Automatically inserts newline characters into sf::Text to wrap words within a pixel width limit.
     *
     * This utility splits the text into words and measures their layout bounds in real-time.
     * It uses the assigned sf::Font and character size from the sf::Text object to calculate
     * precise pixel dimensions, ensuring text is wrapped cleanly at word boundaries (spaces)
     * without breaking words mid-character.
     *
     * @param text The sf::Text object whose internal string will be modified with '\n' characters.
     * @param maxWidth The maximum allowable width of the text block in pixels.
     *
     * @note The sf::Text object must already have a valid font and character size assigned
     *       before calling this function, otherwise geometry calculations will return zero.
     */
    void wrapText(sf::Text& text, float width);
  }
}