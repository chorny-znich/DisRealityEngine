#include "animation_component.h"
#include "sprite_database.h"
#include "ini_parser.h"

namespace dr
{
  /**
   * @brief 
   * @param dt 
   */
  void AnimationComponent::update(float dt)
  {
    mTimer += dt;
    if (mTimer > mFrameDuration) {
      mCurrentFrameIndex++;
      mTimer -= mFrameDuration;
      if (mCurrentFrameIndex >= mCurrentAnimations.size()) {
        mCurrentFrameIndex = 0;
      }
    }
  }

  /**
   * @brief 
   * @return 
   */
  sf::IntRect AnimationComponent::getCurrentRect() const
  {
    return mCurrentAnimations.at(mCurrentFrameIndex);
  }

  /**
   * @brief
   * @param id
   */
  void AnimationComponent::setCurrentAnimation(const std::string& id)
  {
    mCurrentAnimations.clear();
    for (const auto& anim : mAnimations.at(id)) {
      auto info = SpriteDatabase::instance().getSpriteInfo(anim);
      sf::IntRect rect = { {static_cast<int>(info.x), static_cast<int>(info.y)},
        {static_cast<int>(SpriteDatabase::instance().getTileSize().x),
        static_cast<int>(SpriteDatabase::instance().getTileSize().y)} };
      mCurrentAnimations.push_back(rect);
    }
    mCurrentFrameIndex = 0;
    mTimer = 0;
  }
  
  /**
   * @brief Load a list of animations from the file
   * @param filename Path to the file
   */
  void AnimationComponent::loadAnimations(const std::string& filename)
  {
    dr::IniDocument doc = dr::loadIniDocument(filename);

    for (const auto& [key, value] : doc.getSections())
    {
      if (key == "main")
      {
        mTextureId = value.at("texture");
      }
      else
      {
        for (const auto& [sectionKey, sectionValue] : value)
        {
          mAnimations[key].push_back(static_cast<uint16_t>(std::stoi(sectionValue)));
        }
      }
    }
  }
}