#include "level_object.h"

dr::LevelObject::LevelObject(sf::Sprite sprite) :
	mSprite{ sprite }
{
}

void dr::LevelObject::setId(size_t id)
{
	mId = id;
}

size_t dr::LevelObject::getId() const
{
	return mId;
}

void dr::LevelObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}
