#include "engine_utility.h"

namespace dr
{
  namespace EngineUtility
  {
    int16_t getRandomInRange(int16_t min, int16_t max)
    {
      std::random_device rd;
      std::mt19937 rn{ rd() };
      std::uniform_int_distribution distr(min, max);
      return distr(rn);
    }
  }
}