#include "engine_utility.h"
#include <random>

namespace dr {
  size_t EngineUtility::getRandomInRange(size_t min, size_t max)
  {
    std::random_device rd;
    std::mt19937 rn{ rd() };
    std::uniform_int_distribution distr(min, max);
    return distr(rn);
  }
}