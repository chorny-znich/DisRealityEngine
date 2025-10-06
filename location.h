#pragma once
#include <SFML/System/Vector2.hpp>
#include <string>

/**
 * @brief map's unit, usually a tile. The set of locations forms level's map.
*/

namespace dr 
{
	class Location
	{
	private:
		size_t mId;
		sf::Vector2u mPosition;
		std::string mFloorLayerId;
		std::string mLevelLayerId;
		std::string mObjectLayerId;
		bool mPassable{ true };
		bool mEntry{ false };
	public:
		void setId(size_t id);
		size_t getId() const;
		void setPosition(sf::Vector2u pos);
		sf::Vector2u getPosition() const;
		void setFloorLayerId(const std::string& id);
		const std::string& getFloorLayerId() const;
		void setLevelLayerId(const std::string& id);
		const std::string& getLevelLayerId() const;
		void setObjectLayerId(const std::string& id);
		const std::string& getObjectLayerId() const;
		void setPassability(bool value);
		bool isPassable() const;
		void setEntry(bool value);
		bool isEntry() const;
	};
}