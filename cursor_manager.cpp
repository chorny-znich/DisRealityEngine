#include "cursor_manager.h"
#include <iostream>
#include <format>

namespace dr
{
  void CursorManager::init()
  {
    auto& manager = instance();
    // load cursors
    try
    {
      std::optional<sf::Cursor> arrowCursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow);
      manager.mCursors.emplace("arrow", std::move(arrowCursor.value()));
      std::optional<sf::Cursor> handCursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Hand);
      manager.mCursors.emplace("hand", std::move(handCursor.value()));
    }
    catch (const std::exception& e)
    {
      std::cout << std::format("Can't load cursors: {}", e.what());
    }
  }
}