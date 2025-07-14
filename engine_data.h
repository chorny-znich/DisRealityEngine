#pragma once
#include "asset_manager.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace dr
{
  using Textures = AssetManager<std::string, sf::Texture>;
  using Sounds = AssetManager<std::string, sf::SoundBuffer>;
  using Fonts = AssetManager<std::string, sf::Font>;
}