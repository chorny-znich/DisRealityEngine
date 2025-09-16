#include "engine.h"

namespace dr
{
	void Engine::update(sf::Time dt)
	{
		if (!mGameState.isEmpty()) {
			ImGui::SFML::Update(mWindow, dt);
			mGameState.getCurrent()->update(dt);
		}
	}
}