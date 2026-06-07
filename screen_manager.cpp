#include "screen_manager.h"
#include <assert.h>

ScreenManager::ScreenManager() {
	assert(mpManager == nullptr);
	mpManager = this;
}

/**
 * @brief Pop game screen from stack
*/
void ScreenManager::destroyScreen() {
	auto& screens = mpManager->mScreens;
	screens.pop();
}

/**
 * @brief Get active game screen
 * @return shared_ptr to active game screen
*/
std::shared_ptr<Screen> ScreenManager::getCurrent()
{
	auto& screens = mpManager->mScreens;
	assert(!screens.empty());

	return screens.top().second;
}

/**
 * @brief Check if the stack of game screens empty
 * @return Are there any game screens in the stack
*/
bool ScreenManager::isEmpty()
{
	return mScreens.empty();
}