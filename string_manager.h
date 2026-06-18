#pragma once
#include <SFML/System/String.hpp>
#include <string>
#include <unordered_map>

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
    static sf::String get(const std::string& id);
  private:
    StringManager() = default;

    static StringManager& instance()
    {
      static StringManager manager;
      return manager;
    }
    std::unordered_map<std::string, std::string> mStrings;
  };
}