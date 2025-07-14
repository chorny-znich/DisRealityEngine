#pragma once
#include <string>
#include <unordered_map>

/**
 * @brief Parse ini files. Used in:
 * Engine cofiguration files
 * Game maps
 * Player's data
 * Version 1.1.0
 */
namespace dr
{
  using Section = std::unordered_map<std::string, std::string>;

  class IniDocument {
  private:
    std::unordered_map<std::string, Section> mSections;

  public:
    Section& addSection(const std::string& name);
    const Section& getSection(const std::string& name) const;
  };

  IniDocument loadIniDocument(const std::string& filename);
}