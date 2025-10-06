#include "location.h"

namespace dr
{
	void Location::setId(size_t id)
	{
		mId = id;
	}

	size_t Location::getId() const
	{
		return mId;
	}

	void Location::setPosition(sf::Vector2u pos)
	{
		mPosition = pos;
	}

	sf::Vector2u Location::getPosition() const
	{
		return mPosition;
	}

	void Location::setFloorLayerId(const std::string& id)
	{
		mFloorLayerId = id;
	}

	const std::string& Location::getFloorLayerId() const
	{
		return mFloorLayerId;
	}

	void Location::setLevelLayerId(const std::string& id)
	{
		mLevelLayerId = id;
	}

	const std::string& Location::getLevelLayerId() const
	{
		return mLevelLayerId;
	}
	
	void Location::setObjectLayerId(const std::string& id)
	{
		mObjectLayerId = id;
	}

	const std::string& Location::getObjectLayerId() const
	{
		return mObjectLayerId;
	}
	
	void Location::setPassability(bool value)
	{
		mPassable = value;
	}

	bool Location::isPassable() const
	{
		return mPassable;
	}
	void Location::setEntry(bool value)
	{
		mEntry = value;
	}
	bool Location::isEntry() const
	{
		return mEntry;
	}
}