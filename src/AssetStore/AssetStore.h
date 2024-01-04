#ifndef ASSETSTORE_H
#define ASSETSTORE_H

#include <map>
#include <string>
#include <SDL2/SDL.h>

class AssetStore {
    private:
        std::map<std::string, SDL_Texture*> textures;

    public:
        AssetStore();
        ~AssetStore();

        void ClearAssets();
        void AddTextute(SDL_Renderer* renderer, const std::string& assetId, const std::string filePath);
        SDL_Texture* GetTexture(const std::string& assetId);
};

#endif