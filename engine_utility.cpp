#include "engine_utility.h"

namespace dr
{
  namespace EngineUtility
  {
    uint32_t getRandomInRange(uint32_t min, uint32_t max)
    {
      std::random_device rd;
      std::mt19937 rn{ rd() };
      std::uniform_int_distribution distr(min, max);
      return distr(rn);
    }
  }
}