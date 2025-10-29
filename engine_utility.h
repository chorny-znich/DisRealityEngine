#pragma once

namespace dr 
{
  /**
   * @brief a static class with utilities for the DisRealityGF
  */
  class EngineUtility
  {
  public:
    EngineUtility() = delete;
    static size_t getRandomInRange(size_t min, size_t max);
  };
}