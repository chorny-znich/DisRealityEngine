#include "text_manager.h"
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