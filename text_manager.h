#pragma once

#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>

namespace dr
{
	/**
	 * @brief SFML text objects manager singleton class
	*/
	class TextManager
	{
	private:
		std::unordered_map<std::string, sf::Text>	mText;

		static TextManager* mpInstance;

	public:
		TextManager();

		static void	load(const std::string& id, const sf::Text& text);
		static sf::Text& get(const std::string& text);
	};
}