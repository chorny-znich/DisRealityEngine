#include "cursor_manager.h"
#include <iostream>
#include <format>

namespace dr
{
  /**
   * @brief Initialize system cursors 
   */
  void CursorManager::init()
  {
    auto& manager = instance();
    // load cursors
    try
    {
      manager.mCursors.emplace("arrow", sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value());
      manager.mCursors.emplace("hand", sf::Cursor::createFromSystem(sf::Cursor::Type::Hand).value());
    }
    catch (const std::exception& e)
    {
      std::cout << std::format("Can't load cursors: {}", e.what());
    }
  }

  /**
   * @brief get cursor
   * @param id - 
   * @return SFML sf::Cursor
   */
  sf::Cursor& CursorManager::get(const std::string& id)
  {
    auto& manager = instance();
    auto iter = manager.mCursors.find(id);
    assert(iter != manager.mCursors.end());

    return iter->second;
  }
}