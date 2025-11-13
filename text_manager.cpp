#include "text_manager.h"
#include "ini_parser.h"
#include "engine.h"
#include <assert.h>

namespace dr
{
	TextManager* TextManager::mpInstance = nullptr;

	TextManager::TextManager()
	{
		assert(mpInstance == nullptr);
		mpInstance = this;
	}

	/**
	 * @brief Load sf::Text objects from the file
	 */
	void TextManager::init(const std::string& filename)
	{
		auto manager = mpInstance->mText;

		IniDocument doc = loadIniDocument(filename);
		Section section = doc.getSection("size");
		const size_t size = std::stoul(section.at("size"));
		for (size_t i = 0; i < size; i++) {
			Section section = doc.getSection("text_" + std::to_string(i));
			sf::Text text;
			const std::string id = section.at("id");
			text.setFont(Fonts::get(section.at("font")));
			text.setCharacterSize(std::stoul(section.at("character_size")));
			sf::Color color = {
				static_cast<std::uint8_t>(std::stoul(section.at("color_component_red"))),
				static_cast<std::uint8_t>(std::stoul(section.at("color_component_green"))),
				static_cast<std::uint8_t>(std::stoul(section.at("color_component_blue"))),
				static_cast<std::uint8_t>(std::stoul(section.at("color_component_alpha")))
			};
			text.setFillColor(color);
			text.setString(section.at("text"));
			mpInstance->load(id, text);
		}
	}

	/**
	 * @brief 
	 * @param id 
	 * @param text 
	*/
	void TextManager::load(const std::string& id, const sf::Text& text)
	{
		mpInstance->mText[id] = text;
	}

	/**
	 * @brief 
	 * @param text 
	 * @return const SFML Text object
	*/
	sf::Text& TextManager::get(const std::string& text)
	{
		auto& tm = mpInstance->mText;

		auto iter = tm.find(text);
		assert(iter != tm.end());

		return iter->second;
	}
}