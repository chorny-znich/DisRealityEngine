#pragma once
#include <SFML/Graphics.hpp>

namespace dr
{
    /**
     * @brief A base class for all objects that represent architecture of the map
    */
    class LevelObject : public sf::Drawable
    {
    private:
        size_t mId;
    protected:
        sf::Sprite mSprite;
    public:
        LevelObject(sf::Sprite sprite);
        void setId(size_t id);
        size_t getId() const;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
}