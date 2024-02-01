#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include <SDL2/SDL.h>
#include <sol/sol.hpp>
#include <memory>

class LevelLoader {
    public:
        LevelLoader();
        ~LevelLoader();
        void Start(sol::state& lua, const std::unique_ptr<Registry>& registry, const std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer);
    private:
        void LoadLevel(sol::state& lua, const std::unique_ptr<Registry>& registry, const std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer, int level);
        void LoadTileMap(sol::table level, const std::unique_ptr<Registry>& registry);
        void LoadAssets(sol::table level, const std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer);
        void LoadEntities(sol::table level, const std::unique_ptr<Registry>& registry);
};

#endif
