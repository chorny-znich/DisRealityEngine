#include "dynamic_entity.h"

namespace dr
{
	DynamicEntity::DynamicEntity(sf::IntRect rect, const sf::Texture& texture) :
		Entity(rect, texture)
	{
	}
	void DynamicEntity::init(const std::string& id)
	{
		mAnimationComponent.init(id);
	}

	void DynamicEntity::update(float dt)
	{
		mAnimationComponent.update(dt);
		mSprite.setTextureRect(mAnimationComponent.getCurrentRect());
	}
}