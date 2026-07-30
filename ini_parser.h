#pragma once
#include <string>
#include <string_view>
#include <unordered_map>

/**
 * @brief Parse ini files. Used in:
 * Engine cofiguration files
 * Game maps
 * Player's data
 */
namespace dr
{
  using Section = std::unordered_map<std::string, std::string>;

  class IniDocument 
  {
  private:
    std::unordered_map<std::string, Section> mSections;

  public:
    Section& addSection(const std::string& name);
    const Section& getSection(const std::string& name) const;
    bool hasSection(const std::string& name) const;
    const std::unordered_map<std::string, Section>& getSections() const;
    void addKeyValuePair(std::string_view section, std::string_view key, std::string_view data);
  };

  IniDocument loadIniDocument(const std::string& filename);
  void saveIniDocument(std::string_view filename, const IniDocument& doc);
}