#pragma once
#include <string>
#include <map>

namespace dr
{
  /**
 * @brief Manage game texts
 */
  class StringManager
  {
  public:
    StringManager(const StringManager&) = delete;
    StringManager& operator=(const StringManager&) = delete;

    static void init(const std::string& filename);
    static std::string_view get(const std::string& id);
  private:
    StringManager() = default;

    static StringManager& instance()
    {
      static StringManager manager;
      return manager;
    }
    std::map<std::string, std::string> mStrings;
  };
}