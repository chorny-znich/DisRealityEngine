#pragma once
#include "entity.h"
#include "animation_component.h"

namespace dr
{
	class DynamicEntity : public Entity
	{
	public:
		DynamicEntity(sf::IntRect rect, const sf::Texture& texture);
		void init(const std::string& id);
		virtual void update(float dt) override;
	protected:
		AnimationComponent mAnimationComponent;
	};
}