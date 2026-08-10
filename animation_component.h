#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace dr
{
  /**
   * @brief Animate actors on the map
   */
  class AnimationComponent
  {
  public:
    AnimationComponent() = default;
    void init(const std::string& id);
    void update(float dt);
    sf::IntRect getCurrentRect() const;
    void setCurrentAnimation(const std::string& id);
    void loadAnimations(const std::string& filename);
  private:
    std::unordered_map <std::string, std::vector<uint16_t>> mAnimations;
    std::vector<sf::IntRect> mCurrentAnimations;
    std::string mTextureId;
    std::string mCurrentAnimName;
    float mTimer{ 0 };
    float mFrameDuration = 0.125f;
    size_t mCurrentFrameIndex{ 0 };
  };
}