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
		ScreenManager(const ScreenManager&) = delete;
		ScreenManager& operator=(const ScreenManager&) = delete;

		/**
		 * @brief Add game screen to stack
		 * @param shared_ptr on game screen
		*/
		template <typename ScreenPointer>
		static void addScreen(std::string screenId)
		{
			auto& manager = instance();
			std::shared_ptr<ScreenPointer> pScreen = std::make_shared<ScreenPointer>();
			pScreen->init();

			std::shared_ptr<Screen> pBaseScreen = std::static_pointer_cast<Screen>(pScreen);
			manager.mScreens.emplace(screenId, pBaseScreen);
		}

		static void destroyScreen();
		static std::shared_ptr<Screen> getCurrent();
		static bool isEmpty();
	private:
		ScreenManager() = default;

		// Only one instance available
		static ScreenManager& instance()
		{
			static ScreenManager manager;
			return manager;
		}

		std::stack<std::pair<std::string, std::shared_ptr<Screen>>> mScreens;
	};
}

