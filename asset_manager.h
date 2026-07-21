#pragma once
#include "ini_parser.h"
#include <string>
#include <map>
#include <memory>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <iostream>

namespace dr
{
  /**
   * @brief the Asset manager singleton class
   * @tparam Id: asset name
   * @tparam Asset: SFML asset type (texture, font, sound)
   */
  template<typename Id, typename Asset>
  class AssetManager
  {
  public:
    AssetManager(const AssetManager&) = delete;
		AssetManager& operator=(AssetManager&) = delete;
    
		static void init(const std::string& filename);
    static Asset& get(const Id& id);
  private:
	AssetManager() = default;

	static AssetManager& instance()
	{
		static AssetManager manager;
		return manager;
	}
    std::map<std::string, std::string> mAssetList;
    std::map<Id, std::unique_ptr<Asset>> mAssets;

    static bool createAssetList(const std::string& path);
    static Asset& load(const Id& id, const std::string& filename);
  };

	// Realisation

	/**
	 * @brief Initialize and load the assets' list from the file
	 * @tparam Id: asset name
	 * @tparam Asset: SFML asset type (texture, font)
	 * @param filename of the assets list
	*/
	template <typename Id, typename Asset>
	void AssetManager<Id, Asset>::init(const std::string& filename) 
	{
		auto& assetList = instance().mAssetList;
		assetList.clear();
		auto& assets = instance().mAssets;
		assets.clear();
		if (!createAssetList(filename)) {
			throw std::runtime_error("Failed to open the file with the list of assets");
		}
	}

	/**
 * @brief Dynamically loads and compiles an asset from a file on the disk.
 * @tparam Id The asset identifier type.
 * @tparam Asset The SFML resource type (e.g., sf::Texture, sf::Font).
 * @param id The unique identifier to register the loaded asset.
 * @param filename The path to the source file on the disk.
 * @return Asset& A live reference to the newly cached resource.
 * @throws std::runtime_error If the file cannot be opened or parsed by SFML.
 */
	template <typename Id, typename Asset>
	Asset& AssetManager<Id, Asset>::load(const Id& id, const std::string& filename) {
		auto& assets = instance().mAssets;
		std::unique_ptr<Asset> pAsset = std::make_unique<Asset>();
		Asset& result = *pAsset;
		bool success = false;

		if constexpr (std::is_same_v<Asset, sf::Font>)
		{
			success = pAsset->openFromFile(filename);
		}
		else
		{
			success = pAsset->loadFromFile(filename);
		}

		if (!success) {
			throw std::runtime_error("Failed to load asset from " + filename);
		}
		auto iter = assets.insert(std::make_pair(id, std::move(pAsset)));
		assert(iter.second);
		return result;
	}

	/**
 * @brief Retrieves a reference to the requested asset, loading it on-demand if necessary.
 *
 * Implements a Lazy Loading strategy. If the asset is already resident in memory,
 * it returns instantly. Otherwise, it looks up the file path in the registry,
 * compiles the resource via the load() method, and caches it for future frames.
 *
 * @param id The unique identifier assigned to the asset in the configuration registry.
 * @return Asset& A live reference to the requested SFML resource type.
 *
 * @note Triggers an assertion if the requested ID exists neither in active memory
 *       nor in the parsed initialization configuration file.
 */
	template <typename Id, typename Asset>
	Asset& AssetManager<Id, Asset>::get(const Id& id) {
		auto& assets = instance().mAssets;
		auto iter = assets.find(id);
		if (iter == assets.end())
		{
			auto& assetList = instance().mAssetList;
			auto iterList = assetList.find(id);
			assert(iterList != assetList.end());
			return load(id, iterList->second);
		}

		return *iter->second;
	}

	/**
	 * @brief Create the list of assets from ini file
	 * @tparam Id: asset name
	 * @tparam Asset: SFML asset (texture, font)
	 * @param the path to the ini file
	 * @return if the asset list successfully create
	*/
	template <typename Id, typename Asset>
	bool AssetManager<Id, Asset>::createAssetList(const std::string& path) 
	{
		auto& assetList = instance().mAssetList;

		try 
		{
			IniDocument doc = loadIniDocument(path);
			Section section = doc.getSection("assets");

			for (const auto& s : section) 
			{
				auto iter = assetList.insert(std::make_pair(s.first, s.second));
				assert(iter.second);
			}

			return true;
		}
		catch (...) 
		{
			std::cout << "File with the list of assets not found" << std::endl;
		}

		return false;
	}
}