#pragma once
#include <SFML/System.hpp>
#include <string>

/**
 * @brief A map entry which connects with other entry in other map
*/

namespace dr
{
	class MapEntry
	{
	private:
		std::string mId;
		size_t mMapId;
		sf::Vector2u mPosition;
		std::string mLinkedEntryId;
		size_t mVisibility;
	public:
		void setId(const std::string& id);
		std::string getId() const;
		void setMapId(size_t id);
		size_t getMapId() const;
		void setPosition(sf::Vector2u pos);
		sf::Vector2u getPosition() const;
		void setLinkedEntryId(const std::string& id);
		std::string getLinkedEntryId() const;
		void setVisibility(size_t value);
		size_t getVisibility() const;
	};
}