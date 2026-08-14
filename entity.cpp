#include "entity.h"
#include "SFML/Graphics/RenderTarget.hpp"

namespace dr
{
    Entity::Entity(sf::Sprite sprite) :
        mSprite(std::move(sprite)),
        mIsVisible{ true }
    {
    }

    /**
     * @brief
     * @param rect
     * @param texture
     */
    Entity::Entity(sf::IntRect rect, const sf::Texture& texture) :
        mSprite(texture),
        mIsVisible{ true }
    {
        mSprite.setTextureRect(rect);
        mSprite.setPosition({ 0.f, 0.f });
    }

    void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (mIsVisible)
        {
            states.transform *= getTransform();
            target.draw(mSprite, states);
        }
    }

    void Entity::setVisibilityStatus(bool status)
    {
        mIsVisible = status;
    }
}