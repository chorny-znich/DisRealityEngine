#include "architecture_actor.h"

namespace dr
{
	ArchitectureActor::ArchitectureActor(uint16_t id, sf::IntRect rect, sf::Texture& texture) :
		GameActor(rect, texture),
		mId{id}
	{
	}

	/**
	 * @brief Method is empty because the architecture actor is static map element
	 * @param dt delta time
	 */
	void ArchitectureActor::update(float dt)
	{
	}

	uint16_t ArchitectureActor::getID() const
	{
		return mId;
	}
}