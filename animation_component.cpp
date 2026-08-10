#include "animation_component.h"
#include "sprite_database.h"
#include "ini_parser.h"
#include "engine_data.h"

namespace dr
{
    void AnimationComponent::init(const std::string& id)
    {
        dr::IniDocument doc = dr::loadIniDocument(path::Animations.data());
        dr::Section section = doc.getSection("assets");
        const std::string assetName = section.at(id);

        loadAnimations(assetName);
    }

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
        {mFrameSize.x, mFrameSize.y} };
      mCurrentAnimations.push_back(rect);
    }
    mCurrentFrameIndex = 0;
    mTimer = 0;
  }

  void AnimationComponent::setFrameDuration(float duration)
  {
      mFrameDuration = duration;
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
        mFrameSize = {std::stoi(value.at("frame_width")), std::stoi(value.at("frame_height"))};
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