#pragma once
#include "game_object_type.h"
//#include "game_data.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <vector>
#include <memory>

namespace dr
{
  /**
   * @brief A base class for all objects that represent 'loot'. The player can pick up them.
   */
  class GameObject
  {
  public:
    GameObject(GameObjectType type, GameObjectSubType subType, uint16_t spriteID, uint16_t inventorySpriteID);
    void setId(size_t id);
    size_t getId() const;
    void setType(GameObjectType type);
    GameObjectType getType() const;
    void setSubType(GameObjectSubType subType);
    GameObjectSubType getSubType() const;
    void setName(const std::string& name);
    std::string getName() const;
    void setPosition(sf::Vector2i pos);
    sf::Vector2i getPosition() const;
    void setPrice(size_t value);
    size_t getPrice() const;
    void setVisibleStatus(bool value);
    bool isVisible() const;
    void setVisibility(size_t value);
    size_t getVisibility() const;
    void setAmount(size_t value);
    size_t getAmount() const;
    void setSprite(sf::Sprite sprite);
    sf::Sprite getSprite();
    void setInventoryIcon(sf::Sprite sprite);
    sf::Sprite getInventoryIcon();
  protected:
    GameObjectType mType;
    GameObjectSubType mSubType;
    sf::Sprite mCurrentSprite;
    sf::Sprite mInventoryIcon;
  private:
    size_t mId;
    std::string mName;
    sf::Vector2i mPosition;
    
    size_t mPrice;
    bool mVisible;
    size_t mVisibility;
    size_t mAmount;
  };
  using GameObjectPtr = std::shared_ptr<GameObject>;
  using GameObjects = std::vector<std::shared_ptr<GameObject>>;
}