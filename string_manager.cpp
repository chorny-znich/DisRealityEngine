#include "string_manager.h"
#include "ini_parser.h"

namespace dr
{
	/**
 * @brief Load sf::Text objects from the file
 */
	void StringManager::init(const std::string& filename)
	{
		IniDocument doc = loadIniDocument(filename);
		Section section = doc.getSection("size");
		const size_t size = std::stoul(section.at("size"));
		for (size_t i = 0; i < size; i++) 
		{
			Section section = doc.getSection("string_" + std::to_string(i));
			instance().mStrings.emplace(section.)
		}
	}

	static std::string_view get(const std::string& id)
	{

	}
}

