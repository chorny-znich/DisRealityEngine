#pragma once
#include <string>
#include <string_view>
#include <SFML/System/Vector2.hpp>
#include "asset_manager.h"

namespace sf
{
	class Texture;
	class SoundBuffer;
	class Font;
}

namespace dr
{
	using Textures = AssetManager<std::string, sf::Texture>;
	using Sounds = AssetManager<std::string, sf::SoundBuffer>;
	using Fonts = AssetManager<std::string, sf::Font>;

	/**
	 * @brief All pathes to the framework's files
	*/
	namespace path
	{
		constexpr std::string_view EngineConfigFile{ "config/engine_config.ini" };
		constexpr std::string_view TextureList{ "data/texture_list.ini" };
		constexpr std::string_view TileMap{ "data/tile_map.ini" };
		constexpr std::string_view MapsFolder{ "data/maps/" };
		constexpr std::string_view FontsList{ "data/font_list.ini" };
		constexpr std::string_view TextStyle{ "data/text_style.ini" };
		constexpr std::string_view Strings{ "data/strings.ini" };
	}

	/**
	 * @brief Window's resolution state
	 * NATIVE for the current desktop resolution
	 * CUSTOM for the resolution from config file
	*/
	enum class ResolutionState {
		NATIVE,
		CUSTOM
	};

	/**
	 * @brief Window mode
	 * WINDOW for the window mode
	 * FULLSCREEN for the fullscreen mode
	*/
	enum class WindowMode {
		WINDOW,
		FULLSCREEN
	};

	/**
	 * @brief Structure for the engine configuration, reading from 'config/engine_config.ini'
	 * mTitle -- the game title
	*/
	struct EngineConfig
	{
		std::string mTitle;
	};

	/**
		* @brief the structure for window configuration
		*
		* mResolutionState from ResolutionState enum {NATIVE: desktop resolution, CUSTOM: user resolution}
		* mResolution -- sf::vector2u(resolution.x, resolution.y) work if mResolutionState = CUSTOM
		* mWindowMode from WindowMode enum {WINDOW:, FULLSCREEN: }
		*/
	struct WindowConfig
	{
		ResolutionState mResolutionState;
		sf::Vector2u mResolution;
		WindowMode mWindowMode;
	};
}