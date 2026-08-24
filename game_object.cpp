#include "game_object.h"
#include "sprite_database.h"

namespace dr
{
  GameObject::GameObject(GameObjectType type, GameObjectSubType subType, uint16_t spriteID, uint16_t inventorySpriteID) :
    mType{ type },
    mSubType{ subType },
    mCurrentSprite( dr::SpriteDatabase::instance().getSprite(spriteID)),
    mInventoryIcon{ dr::SpriteDatabase::instance().getSprite(spriteID) },
    mPrice{ 0 },
    mVisible{ false },
    mVisibility{ 0 },
    mAmount{ 0 }
  {
  }

  void GameObject::setId(size_t id)
  {
    mId = id;
  }

  size_t GameObject::getId() const
  {
    return mId;
  }

  void GameObject::setType(GameObjectType type)
  {
    mType = type;
  }

  GameObjectType GameObject::getType() const
  {
    return mType;
  }

  void GameObject::setSubType(GameObjectSubType subType)
  {
    mSubType = subType;
  }

  GameObjectSubType GameObject::getSubType() const
  {
    return mSubType;
  }

  void GameObject::setName(const std::string& name)
  {
    mName = name;
  }

  std::string GameObject::getName() const
  {
    return mName;
  }

  void GameObject::setPosition(sf::Vector2i pos)
  {
    mPosition = pos;
    mCurrentSprite.setPosition({ static_cast<float>(dr::SpriteDatabase::instance().getTileSize().x * mPosition.x), 
      static_cast<float>(dr::SpriteDatabase::instance().getTileSize().y * mPosition.y) });
  }

  sf::Vector2i GameObject::getPosition() const
  {
    return mPosition;
  }

  void GameObject::setPrice(size_t value)
  {
    mPrice = value;
  }

  size_t GameObject::getPrice() const
  {
    return mPrice;
  }

  void GameObject::setVisibleStatus(bool value)
  {
    mVisible = value;
  }

  bool GameObject::isVisible() const
  {
    return mVisible;
  }

  void GameObject::setVisibility(size_t value)
  {
    mVisibility = value;
  }

  size_t GameObject::getVisibility() const
  {
    return mVisibility;
  }

  void GameObject::setAmount(size_t value)
  {
    mAmount = value;
  }

  size_t GameObject::getAmount() const
  {
    return mAmount;
  }

  void GameObject::setSprite(sf::Sprite sprite)
  {
    mCurrentSprite = sprite;
  }

  sf::Sprite GameObject::getSprite()
  {
    return mCurrentSprite;
  }

  void GameObject::setInventoryIcon(sf::Sprite sprite)
  {
    mInventoryIcon = sprite;
  }

  sf::Sprite GameObject::getInventoryIcon()
  {
    return mInventoryIcon;
  }
}