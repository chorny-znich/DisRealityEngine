#pragma once
#include <string>
#include <unordered_map>
#include <SFML/Window/Cursor.hpp>

namespace dr
{
  /**
   * @brief Manage cursors
   */
  class CursorManager
  {
  public:
    CursorManager(const CursorManager&) = delete;
    CursorManager& operator=(const CursorManager&) = delete;

    static void init();
  private:
    CursorManager() = default;

    static CursorManager& instance()
    {
      static CursorManager manager;
      return manager;
    }

    std::unordered_map<std::string, sf::Cursor> mCursors;
  };
}