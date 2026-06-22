#include "imgui_helper.h"
#include <cassert>

namespace dr
{
	void ImguiHelper::init(sf::RenderWindow* pWindow)
	{
		mWindow = pWindow;
	}

	void ImguiHelper::update(sf::Time time)
	{
		mDtTime = time;
	}

	sf::RenderWindow& ImguiHelper::getWindow()
	{
		assert(mWindow != nullptr);
		return *mWindow;
	}

	sf::Time ImguiHelper::getTime()
	{
		return mDtTime;
	}
}