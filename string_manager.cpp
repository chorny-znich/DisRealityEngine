#include "string_manager.h"
#include "ini_parser.h"
#include <assert.h>

namespace dr
{
	/**
 * @brief Load list of strings from the ini file
 */
	void StringManager::init(const std::string& filename)
	{
		IniDocument doc = loadIniDocument(filename);
		instance().mStrings = doc.getSection("strings");
	}

	/**
	 * @brief Get a localized string converted to Unicode for SFML 3 text rendering
	 * @param id The unique identifier of the string in the localization map
	 * @return sf::String encoded in UTF-32, decoded from internal UTF-8 storage
	 * @note Triggers an assertion if the requested ID does not exist in the map 
	 */
	sf::String StringManager::get(const std::string& id)
	{
		auto& strings = instance().mStrings;

		auto iter = strings.find(id);
		assert(iter != strings.end());

		return sf::String::fromUtf8(iter->second.begin(), iter->second.end());
	}
}