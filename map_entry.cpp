#include "map_entry.h"

namespace dr
{
	void MapEntry::setId(const std::string& id)
	{
		mId = id;
	}

	std::string MapEntry::getId() const
	{
		return mId;
	}

	void MapEntry::setMapId(size_t id)
	{
		mMapId = id;
	}

	size_t MapEntry::getMapId() const
	{
		return mMapId;
	}

	void MapEntry::setPosition(sf::Vector2u pos)
	{
		mPosition = pos;
	}

	sf::Vector2u MapEntry::getPosition() const
	{
		return mPosition;
	}

	void MapEntry::setLinkedEntryId(const std::string& id)
	{
		mLinkedEntryId = id;
	}

	std::string MapEntry::getLinkedEntryId() const
	{
		return mLinkedEntryId;
	}

	void MapEntry::setVisibility(size_t value)
	{
		mVisibility = value;
	}

	size_t MapEntry::getVisibility() const
	{
		return mVisibility;
	}
}