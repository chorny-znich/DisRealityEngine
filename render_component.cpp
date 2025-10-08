#include "render_component.h"
#include "engine_data.h"
#include <algorithm>

namespace dr
{
    void RenderComponent::updateFloorLayer(const sf::VertexArray& arr)
    {
        mFloorLayer = arr;
    }

    void RenderComponent::addLevelObject(std::unique_ptr<LevelObject> obj)
    {
        mLevelLayer.push_back(std::move(obj));
    }

    void RenderComponent::deleteLevelObject(size_t id)
    {
        mLevelLayer.erase(std::remove_if(mLevelLayer.begin(), mLevelLayer.end(), [id](auto& obj) {
            return obj->getId() == id;
            }), mLevelLayer.end());
    }

    
    void RenderComponent::addStaticObject(std::unique_ptr<StaticObject> obj)
    {
        mStaticLayer.push_back(std::move(obj));
    }

    void RenderComponent::deleteStaticObject(size_t id)
    {
        mStaticLayer.erase(std::remove_if(mStaticLayer.begin(), mStaticLayer.end(), [id](auto& obj) {
            return obj->getId() == id;
            }), mStaticLayer.end());
    }

    /*
    void RenderComponent::addDynamicActor(sf::Sprite& sprite)
    {
        mDynamicActor.push_back(sprite);
    }
    */
    void RenderComponent::render(sf::RenderWindow& window)
    {
        window.draw(mFloorLayer, &(Textures::get("floor_texture")));
        for (const auto& ll : mLevelLayer) {
            window.draw(*ll);
        }
        for (const auto& sl : mStaticLayer) {
            window.draw(*sl);
        }
        /*for (const auto& da : mDynamicActor) {
            window.draw(da);
        }*/
    }
}