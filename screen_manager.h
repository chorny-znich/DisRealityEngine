#pragma once
#include "screen.h"
#include <string>
#include <stack>
#include <memory>


namespace dr
{
	/**
	 * @brief Game state management
	 */
	class ScreenManager
	{
	public:
		ScreenManager();

		/**
		 * @brief Add game screen to stack
		 * @param shared_ptr on game screen
		*/
		template <typename ScreenPointer>
		static void addScreen(std::string screenId)
		{
			std::shared_ptr<ScreenPointer> pScreen = std::make_shared<ScreenPointer>();
			pScreen->init();

			auto& screens = mpManager->mScreens;
			screens.push({ screenId, pScreen });
		}

		static void destroyScreen();
		static std::shared_ptr<Screen> getCurrent();
		static bool isEmpty();
	private:
		inline static ScreenManager* mpManager;
		inline static std::stack<std::pair<std::string, std::shared_ptr<Screen>>> mScreens;
	};
}

