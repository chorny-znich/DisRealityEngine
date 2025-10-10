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
		const LevelObjects mLevelLayer;
		//StaticObjects& mStaticLayer;
	public:
		void updateFloorLayer(const sf::VertexArray& arr);
		void render(sf::RenderWindow& window);
	};
}