#include "engine_utility.h"

namespace dr
{
  namespace EngineUtility
  {
    /**
     * @brief 
     * @param min 
     * @param max If maximum value is lesser than minimum value it become equal to the minimum value
     * @return Random number in range 
     */
    int16_t getRandomInRange(int16_t min, int16_t max)
    {
      static std::random_device rd;
      static std::mt19937 rn{ rd() };
      
      if (min > max)
      {
        max = min;
      }
      std::uniform_int_distribution distr(min, max);
      return distr(rn);
    }
  }
}