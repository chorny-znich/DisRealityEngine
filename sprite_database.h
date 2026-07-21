#pragma once
#include <string>
#include <unordered_map>
#include <cstdint>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace dr
{
	enum class SpriteCategory : std::uint8_t
	{
		Floor,
		Wall,
		Decoration,
		Item,
		UI,
		Unknown
	};

	struct SpriteInfo {
		std::uint16_t spriteId;
		std::string textureId;
		float x;
		float y;
		SpriteCategory type;
	};

	class SpriteDatabase
	{
	private:
		SpriteDatabase() = default;
	public:
		SpriteDatabase(const SpriteDatabase&) = delete;
		SpriteDatabase& operator=(const SpriteDatabase&) = delete;
		static SpriteDatabase& instance()
		{
			static SpriteDatabase database;
			return database;
		}

		void init();
		sf::Vector2f getSpriteCoords(uint16_t id) const;
		sf::Sprite getSprite(uint16_t id) const;
		SpriteInfo getSpriteInfo(uint16_t id) const;
		std::vector<std::uint16_t> getIdByCategory(SpriteCategory);
	private:
		sf::Vector2i mTileSize{ 0, 0 };
		std::unordered_map<uint16_t, SpriteInfo> mSpriteMap;
	};
}