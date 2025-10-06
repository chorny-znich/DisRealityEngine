#include "static_object.h"

namespace dr
{
	StaticObject::StaticObject(sf::Sprite sprite) : 
		mSprite{ sprite }
	{
	}

	void StaticObject::setId(size_t id)
	{
		mId = id;
	}

	size_t StaticObject::getId() const
	{
		return mId;
	}

	void StaticObject::update(sf::Time dt)
	{
	}

	void StaticObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(mSprite, states);
	}
}