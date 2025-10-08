#pragma once
#include "level_object.h"
#include "static_object.h"
#include <SFML/Graphics.hpp>
#include <vector>

/**
 * @brief Component for render graphics
*/

namespace dr
{
	class RenderComponent
	{
	private:
		sf::VertexArray mFloorLayer;
		std::vector<std::unique_ptr<LevelObject>> mLevelLayer;
		std::vector<std::unique_ptr<StaticObject>> mStaticLayer;
		//std::vector<sf::Sprite> mDynamicActor;
	public:
		void updateFloorLayer(const sf::VertexArray& arr);
		void addLevelObject(std::unique_ptr<LevelObject> obj);
		void deleteLevelObject(size_t id);
		void addStaticObject(std::unique_ptr<StaticObject> obj);
		void deleteStaticObject(size_t id);
		//void addDynamicActor(sf::Sprite& sprite);
		void render(sf::RenderWindow& window);
	};
}