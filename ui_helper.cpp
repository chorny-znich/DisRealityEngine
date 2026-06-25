#include "ui_helper.h"
#include <SFML/System/String.hpp>
#include <vector>

void dr::UIHelper::wrapText(sf::Text& text, float width)
{
  sf::String str = text.getString();
  std::vector<sf::String> strings;

  // Divide the string into the words
  int point{ 0 };
  for (size_t i{0}; i < str.getSize(); i++)
  {
    if (str[i] == ' ')
    {
      sf::String word = str.substring(point, i + 1);
      strings.push_back(std::move(word));
      point = i + 1;
    }
  }
  strings.push_back(str.substring(point));

  sf::String result{};
  sf::String currentLine{};
}