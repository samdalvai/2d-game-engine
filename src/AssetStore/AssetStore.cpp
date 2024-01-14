#include "./AssetStore.h"
#include "../Logger/Logger.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <vector>
#include <sstream>

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

SDL_Texture* AssetStore::GetTexture(const std::string& assetId) {
    return textures[assetId];
}

