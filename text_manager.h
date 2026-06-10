#pragma once
#include <string>
#include <unordered_map>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>

namespace dr
{
	/**
 * @brief Text settings
 * font size, character size, color
 */
	struct TextStyle
	{
		std::string mFont{};
		int mCharacterSize{ 14 };
		sf::Color mColor{ 0, 0, 0, 255 };
	};

	/**
	* @brief Create SFML sf::Text object with given style
	*/
	class TextManager
	{
	public:
		TextManager(const TextManager&) = delete;
		TextManager& operator=(const TextManager&) = delete;

		static void init(const std::string& filename);
		static void	load(const std::string& id, TextStyle textStyle);
		static sf::Text get(const std::string& id);
	private:
		TextManager() = default;

		std::unordered_map<std::string, TextStyle>	mStyle;

		static TextManager& instance()
		{
			static TextManager manager;
			return manager;
		}
	};
}