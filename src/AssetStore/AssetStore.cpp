#include "./AssetStore.h"
#include "../Logger/Logger.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <list>

AssetStore::AssetStore() {
    Logger::Log("Asset store constructor called");
}

AssetStore::~AssetStore(){
    ClearAssets();
    Logger::Log("Asset store destructor called");
}

void AssetStore::ClearAssets() {
    for (auto texture : textures) {
        SDL_DestroyTexture(texture.second);
    }

    textures.clear();
}

void AssetStore::AddTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string filePath) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (surface == nullptr) {
        Logger::Err("Error loading texture file: " + filePath);
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    textures.emplace(assetId, texture);

    Logger::Log("New texture added to the asset store with id: " + assetId);
}

void AssetStore::AddTileMap(const std::string& assetId, const std::string filePath) {
    std::ifstream mapFile(filePath);

    if (!mapFile.is_open()) {
        Logger::Err("Error: Unable to open file: " + filePath);
    }

    std::vector<std::vector<int>>* mapData = new std::vector<std::vector<int>>();

    std::string line;
    while (std::getline(mapFile, line)) {
        std::cout << line << std::endl;
        std::vector<int> rowData;

        std::istringstream iss(line);
        std::string token;
    
        while (std::getline(iss, token, ',')) {
            int value;
            std::istringstream(token) >> value;
            rowData.push_back(value);
        }

        mapData->push_back(rowData);
    }

    mapFile.close();

    tileMaps.emplace(assetId, mapData);

    Logger::Log("New tile map added to the asset store with id: " + assetId);
}

SDL_Texture* AssetStore::GetTexture(const std::string& assetId) {
    return textures[assetId];
}

std::vector<std::vector<int>>* AssetStore::GetTileMap(const std::string& assetId) {
    return tileMaps[assetId];
}

