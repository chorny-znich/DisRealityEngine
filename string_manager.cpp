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
	 * @brief get the text string
	 * @param id - string
	 * @return text string
	 */
	std::string StringManager::get(std::string id)
	{
		auto& strings = instance().mStrings;

		auto iter = strings.find(id);
		assert(iter != strings.end());

		return iter->second;
	}
}