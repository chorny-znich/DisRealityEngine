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
    static Asset& get(Id id);
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
    static void load(Id id, const std::string& filename);
  };

	// Realisation

	/**
	 * @brief Initialize and load the assets' list from the file
	 * @tparam Id: asset name
	 * @tparam Asset: SFML asset type (texture, font)
	 * @param filename of the assets list
	*/
	template <typename Id, typename Asset>
	void AssetManager<Id, Asset>::init(const std::string& filename) {
		auto& assetList = instance().mAssetList;
		if (!createAssetList(filename)) {
			throw std::runtime_error("Failed to open the file with the list of assets");
		}

		for (const auto& asset : assetList) {
			load(asset.first, asset.second);
		}
	}

	/**
	 * @brief load the asset from the file
	 * @tparam Id: asset name
	 * @tparam Asset: SFML asset type (texture, font)
	 * @param id of the asset
	 * @param the filename of the asset
	*/
	template <typename Id, typename Asset>
	void AssetManager<Id, Asset>::load(Id id, const std::string& filename) {
		auto& assets = instance().mAssets;
		std::unique_ptr<Asset> pAsset = std::make_unique<Asset>();
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
	}

	/**
		 * @brief get reference to the asset
		 * @tparam Asset name
		 * @tparam Asset type
		 * @param id of the asset
		 * @return reference to the asset
		*/
	template <typename Id, typename Asset>
	Asset& AssetManager<Id, Asset>::get(Id id) {
		auto& assets = instance().mAssets;
		auto iter = assets.find(id);
		assert(iter != assets.end());

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