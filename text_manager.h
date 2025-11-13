#pragma once

#include "engine_data.h"
#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>

namespace dr
{
	/**
	 * @brief Create SFML text object with given style
	*/
	class TextManager
	{
	private:
		std::unordered_map<std::string, sf::Text>	mStyle;

		static TextManager* mpInstance;

	public:
		TextManager();

		static void init(const std::string& filename);
		static void	load(const std::string& id, const sf::Text& text);
		static sf::Text get(const std::string& id);
	};
}