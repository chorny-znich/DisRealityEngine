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
		LevelObjects mLevelLayer;
		StaticObjects mStaticLayer;
	public:
		void updateFloorLayer(const sf::VertexArray& arr);
		void updateLevelLayer(LevelObjects& objs);
		void updateStaticLayer(StaticObjects& objs);
		void render(sf::RenderWindow& window);
	};
}