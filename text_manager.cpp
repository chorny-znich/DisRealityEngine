#include "text_manager.h"
#include "ini_parser.h"
//#include "engine_data.h"
//#include <memory>

namespace dr
{
	/**
	 * @brief Load sf::Text objects from the file
   */
	void TextManager::init(const std::string& filename)
	{
		IniDocument doc = loadIniDocument(filename);
		Section section = doc.getSection("size");
		const size_t size = std::stoul(section.at("size"));
		for (size_t i = 0; i < size; i++) {
			Section section = doc.getSection("style_" + std::to_string(i));
			TextStyle textStyle;
			textStyle.mFont = section.at("font");
			const std::string id = section.at("id");
			textStyle.mCharacterSize = std::stoul(section.at("character_size"));
			sf::Color color = {
				static_cast<std::uint8_t>(std::stoul(section.at("color_component_red"))),
				static_cast<std::uint8_t>(std::stoul(section.at("color_component_green"))),
				static_cast<std::uint8_t>(std::stoul(section.at("color_component_blue"))),
				static_cast<std::uint8_t>(std::stoul(section.at("color_component_alpha")))
			};
			textStyle.mColor = color;

			load(id, textStyle);
		}
	}

	/**
	 * @brief add a style to the manager
	 * @param id - string id
	 * @param text - sf::Text object from SFML3
	*/
	void TextManager::load(const std::string& id, TextStyle textStyle)
	{
		instance().mStyle[id] = textStyle;
	}

	/**
	 * @brief Create and return sf::Text objects
	 * @param text - style's id as std::string
	 * @return const SFML Text object
	*/
	sf::Text TextManager::get(const std::string& id)
	{
		auto& styles = instance().mStyle;

		auto iter = styles.find(id);
		assert(iter != styles.end());

		TextStyle textStyle = iter->second;
		std::unique_ptr<sf::Text> text = std::make_unique<sf::Text>(Fonts::get(textStyle.mFont));
		text->setCharacterSize(textStyle.mCharacterSize);
		text->setFillColor(textStyle.mColor);

		return *text;
	}
}