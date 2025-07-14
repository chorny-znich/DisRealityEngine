#pragma once
#include "ini_parser.h"
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <stdexcept>
#include <cassert>

namespace dr
{
	/**
	 * @brief the Asset manager singleton class
	 * @tparam Id: asset name
	 * @tparam Asset: SFML asset type (texture, font, sound)
	*/
	template <typename Id, typename Asset>
	class AssetManager {
	private:
		std::map<std::string, std::string> mAssetList;
		std::map<Id, std::unique_ptr<Asset>> mAssets;
		static inline AssetManager<Id, Asset>* mpAssetManager = nullptr;

		static bool createAssetList(const std::string& path);
		static void load(Id id, const std::string& filename);

	public:
		AssetManager();
		static void init(const std::string& filename);

		static Asset& get(Id id);
	};

	//	Realisation

	template <typename Id, typename Asset>
	AssetManager<Id, Asset>::AssetManager() {
		assert(mpAssetManager == nullptr);
		mpAssetManager = this;
	}

	/**
	 * @brief Initialize and load the assets' list from the file
	 * @tparam Id: asset name
	 * @tparam Asset: SFML asset type (texture, font)
	 * @param filename of the assets list
	*/
	template <typename Id, typename Asset>
	void AssetManager<Id, Asset>::init(const std::string& filename) {
		auto& assetList = mpAssetManager->mAssetList;
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
		auto& assets = mpAssetManager->mAssets;
		std::unique_ptr<Asset> pAsset = std::make_unique<Asset>();
		if (!pAsset->loadFromFile(filename)) {
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
		auto& assets = mpAssetManager->mAssets;
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
	bool AssetManager<Id, Asset>::createAssetList(const std::string& path) {
		auto& assetList = mpAssetManager->mAssetList;

		try {
			IniDocument doc = loadIniDocument(path);
			Section section = doc.getSection("assets");

			for (const auto& s : section) {
				auto iter = assetList.insert(std::make_pair(s.first, s.second));
				assert(iter.second);
			}

			return true;
		}
		catch (...) {
			std::cout << "File with the list of assets not found" << std::endl;
		}

		return false;
	}
}