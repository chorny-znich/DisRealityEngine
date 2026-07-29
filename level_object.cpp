#include "level_object.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace dr
{
	dr::LevelObject::LevelObject(uint16_t id, sf::IntRect rect, sf::Texture& texture) :
		mId{id},
		mSprite{ texture }
	{
		mSprite.setTextureRect(rect);
	}

	void dr::LevelObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(mSprite, states);
	}

	void LevelObject::setPosition(sf::Vector2f pos)
	{
		mSprite.setPosition(pos);
	}
	uint16_t LevelObject::getID() const
	{
		return mId;
	}
}