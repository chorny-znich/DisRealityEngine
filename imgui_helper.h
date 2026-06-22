#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

namespace dr
{
	class ImguiHelper
	{
	public:
		ImguiHelper() = delete;

		static void init(sf::RenderWindow* pWindow);
		static void update(sf::Time time);
		static sf::RenderWindow& getWindow();
		static sf::Time getTime();
	private:
		inline static sf::RenderWindow* mWindow{nullptr};
		inline static sf::Time mDtTime{sf::Time::Zero};
	};
}

