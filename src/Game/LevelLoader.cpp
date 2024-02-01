#include "./LevelLoader.h"
#include "./Game.h"

#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/KeyboardControlledComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/TextLabelComponent.h"
#include "../Components/ScriptComponent.h"

#include <fstream>
#include <string>
#include <sol/sol.hpp>

LevelLoader::LevelLoader() {
    Logger::Log("LevelLoader constructor called!");    
}

LevelLoader::~LevelLoader() {
    Logger::Log("LevelLoader destructor called!");    
}

void LevelLoader::Start(sol::state& lua, const std::unique_ptr<Registry>& registry, const std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer) {
    sol::load_result script = lua.load_file("./assets/configuration/Configuration.lua");
    if (!script.valid()) {
        sol::error err = script;
        std::string errorMessage = err.what();
        Logger::Err("Error loading the lua script: " + errorMessage);
        return;
    }

    lua.script_file("./assets/configuration/Configuration.lua");

    sol::table config = lua["Config"];
    int level = config["level"];

    LoadLevel(lua, registry, assetStore, renderer, level);
}

void LevelLoader::LoadLevel(sol::state& lua, const std::unique_ptr<Registry>& registry, const std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer, int levelNumber) {
    // This checks the syntax of our script, but it does not execute the script
    sol::load_result script = lua.load_file("./assets/scripts/Level" + std::to_string(levelNumber) + ".lua");
    if (!script.valid()) {
        sol::error err = script;
        std::string errorMessage = err.what();
        Logger::Err("Error loading the lua script: " + errorMessage);
        return;
    }

    // Executes the script using the Sol state
    lua.script_file("./assets/scripts/Level" + std::to_string(levelNumber) + ".lua");

    // Read the big table for the current level
    sol::table level = lua["Level"];

    LoadAssets(level, assetStore, renderer);

    LoadTileMap(level, registry);

    LoadEntities(level, registry);
}

void LevelLoader::LoadAssets(sol::table level, const std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer) {
    ////////////////////////////////////////////////////////////////////////////
    // Read the level assets
    ////////////////////////////////////////////////////////////////////////////
    sol::table assets = level["assets"];

    int i = 0;
    while (true) {
        sol::optional<sol::table> hasAsset = assets[i];
        if (hasAsset == sol::nullopt) {
            break;
        }
        sol::table asset = assets[i];
        std::string assetType = asset["type"];
        std::string assetId = asset["id"];
        if (assetType == "texture") {
            assetStore->AddTexture(renderer, assetId, asset["file"]);
            Logger::Log("A new texture asset was added to the asset store, id: " + assetId);
        }
        if (assetType == "font") {
            assetStore->AddFont(assetId, asset["file"], asset["font_size"]);
            Logger::Log("A new font asset was added to the asset store, id: " + assetId);
        }
        i++;
    }
}

void LevelLoader::LoadTileMap(sol::table level, const std::unique_ptr<Registry>& registry) {
    sol::table map = level["tilemap"];
    std::string mapFilePath = map["map_file"];
    std::string mapTextureAssetId = map["texture_asset_id"];
    int tileSize = map["tile_size"];
    double mapScale = map["scale"];

    std::ifstream mapFile(mapFilePath);

    if (!mapFile.is_open()) {
        Logger::Err("Error: Unable to open file: " + mapFilePath);
    }

    std::string line;

    int rowNumber = 0;
    int columnNumber = 0;
    while (std::getline(mapFile, line)) {
        std::istringstream ss(line);
        std::string value;

        columnNumber = 0;
        while (std::getline(ss, value, ',')) {
            int tileNumber = std::stoi(value);

            int srcRectX = tileNumber % 10 * tileSize;
            int srcRectY = tileNumber / 10 * tileSize;

            Entity tile = registry->CreateEntity();
            tile.AddComponent<TransformComponent>(glm::vec2(columnNumber * (mapScale * tileSize), rowNumber * (mapScale * tileSize)), glm::vec2(mapScale, mapScale), 0.0);
            tile.AddComponent<SpriteComponent>(mapTextureAssetId, tileSize, tileSize, 0, false, srcRectX, srcRectY);
            columnNumber++;
        }

        rowNumber++;
    }

    Game::mapWidth = columnNumber * tileSize * mapScale;
    Game::mapHeight = rowNumber * tileSize * mapScale;
    mapFile.close();
}

void LevelLoader::LoadEntities(sol::table level, const std::unique_ptr<Registry>& registry) {

    ////////////////////////////////////////////////////////////////////////////
    // Read the level entities and their components
    ////////////////////////////////////////////////////////////////////////////
    sol::table entities = level["entities"];
    int i = 0;
    while (true) {
        sol::optional<sol::table> hasEntity = entities[i];
        if (hasEntity == sol::nullopt) {
            break;
        }

        sol::table entity = entities[i];

        Entity newEntity = registry->CreateEntity();

        // Tag
        sol::optional<std::string> tag = entity["tag"];
        if (tag != sol::nullopt) {
            newEntity.Tag(entity["tag"]);
        }

        // Group
        sol::optional<std::string> group = entity["group"];
        if (group != sol::nullopt) {
            newEntity.Group(entity["group"]);
        }

        // Components
        sol::optional<sol::table> hasComponents = entity["components"];
        if (hasComponents != sol::nullopt) {
            // Transform
            sol::optional<sol::table> transform = entity["components"]["transform"];
            if (transform != sol::nullopt) {
                newEntity.AddComponent<TransformComponent>(
                    glm::vec2(
                        entity["components"]["transform"]["position"]["x"],
                        entity["components"]["transform"]["position"]["y"]
                    ),
                    glm::vec2(
                        entity["components"]["transform"]["scale"]["x"].get_or(1.0),
                        entity["components"]["transform"]["scale"]["y"].get_or(1.0)
                    ),
                    entity["components"]["transform"]["rotation"].get_or(0.0)
                );
            }

            // RigidBody
            sol::optional<sol::table> rigidbody = entity["components"]["rigidbody"];
            if (rigidbody != sol::nullopt) {
                newEntity.AddComponent<RigidBodyComponent>(
                    glm::vec2(
                        entity["components"]["rigidbody"]["velocity"]["x"].get_or(0.0),
                        entity["components"]["rigidbody"]["velocity"]["y"].get_or(0.0)
                    ),
                    glm::vec2(
                        entity["components"]["rigidbody"]["direction"]["x"].get_or(0.0),
                        entity["components"]["rigidbody"]["direction"]["y"].get_or(0.0)
                    )
                );
            }

            // Sprite
            sol::optional<sol::table> sprite = entity["components"]["sprite"];
            if (sprite != sol::nullopt) {
                newEntity.AddComponent<SpriteComponent>(
                    entity["components"]["sprite"]["texture_asset_id"],
                    entity["components"]["sprite"]["width"],
                    entity["components"]["sprite"]["height"],
                    entity["components"]["sprite"]["z_index"].get_or(1),
                    entity["components"]["sprite"]["fixed"].get_or(false),
                    entity["components"]["sprite"]["src_rect_x"].get_or(0),
                    entity["components"]["sprite"]["src_rect_y"].get_or(0)
                );
            }

            // Animation
            sol::optional<sol::table> animation = entity["components"]["animation"];
            if (animation != sol::nullopt) {
                newEntity.AddComponent<AnimationComponent>(
                    entity["components"]["animation"]["num_frames"].get_or(1),
                    entity["components"]["animation"]["speed_rate"].get_or(1)
                );
            }

            // BoxCollider
            sol::optional<sol::table> collider = entity["components"]["boxcollider"];
            if (collider != sol::nullopt) {
                newEntity.AddComponent<BoxColliderComponent>(
                    entity["components"]["boxcollider"]["width"],
                    entity["components"]["boxcollider"]["height"],
                    glm::vec2(
                        entity["components"]["boxcollider"]["offset"]["x"].get_or(0),
                        entity["components"]["boxcollider"]["offset"]["y"].get_or(0)
                    )
                );
            }
            
            // Health
            sol::optional<sol::table> health = entity["components"]["health"];
            if (health != sol::nullopt) {
                newEntity.AddComponent<HealthComponent>(
                    static_cast<int>(entity["components"]["health"]["health_percentage"].get_or(100))
                );
            }
            
            // ProjectileEmitter
            sol::optional<sol::table> projectileEmitter = entity["components"]["projectile_emitter"];
            if (projectileEmitter != sol::nullopt) {
                newEntity.AddComponent<ProjectileEmitterComponent>(
                    glm::vec2(
                        entity["components"]["projectile_emitter"]["projectile_velocity"]["x"],
                        entity["components"]["projectile_emitter"]["projectile_velocity"]["y"]
                    ),
                    static_cast<int>(entity["components"]["projectile_emitter"]["repeat_frequency"].get_or(1)) * 1000,
                    static_cast<int>(entity["components"]["projectile_emitter"]["projectile_duration"].get_or(10)) * 1000,
                    static_cast<int>(entity["components"]["projectile_emitter"]["hit_percentage_damage"].get_or(10)),
                    entity["components"]["projectile_emitter"]["friendly"].get_or(false)
                );
            }

            // CameraFollow
            sol::optional<sol::table> cameraFollow = entity["components"]["camera_follow"];
            if (cameraFollow != sol::nullopt) {
                newEntity.AddComponent<CameraFollowComponent>();
            }

            // KeyboardControlled
            sol::optional<sol::table> keyboardControlled = entity["components"]["keyboard_controller"];
            if (keyboardControlled != sol::nullopt) {
                newEntity.AddComponent<KeyboardControlledComponent>(
                    glm::vec2(
                        entity["components"]["keyboard_controller"]["up_velocity"]["x"],
                        entity["components"]["keyboard_controller"]["up_velocity"]["y"]
                    ),
                    glm::vec2(
                        entity["components"]["keyboard_controller"]["right_velocity"]["x"],
                        entity["components"]["keyboard_controller"]["right_velocity"]["y"]
                    ),
                    glm::vec2(
                        entity["components"]["keyboard_controller"]["down_velocity"]["x"],
                        entity["components"]["keyboard_controller"]["down_velocity"]["y"]
                    ),
                    glm::vec2(
                        entity["components"]["keyboard_controller"]["left_velocity"]["x"],
                        entity["components"]["keyboard_controller"]["left_velocity"]["y"]
                    )
                );
            }

            // Text label
            sol::optional<sol::table> textLabel = entity["components"]["text_label"];
            if (textLabel != sol::nullopt) {
                SDL_Color color = { 
                    static_cast<Uint8>(entity["components"]["text_label"]["color"]["r"].get_or(255)), 
                    static_cast<Uint8>(entity["components"]["text_label"]["color"]["g"].get_or(255)),
                    static_cast<Uint8>(entity["components"]["text_label"]["color"]["b"].get_or(255))
                };

                newEntity.AddComponent<TextLabelComponent>(
                    glm::vec2(
                        static_cast<int>(entity["components"]["text_label"]["position"]["x"]),
                        static_cast<int>(entity["components"]["text_label"]["position"]["y"])
                    ),
                    entity["components"]["text_label"]["text"],
                    entity["components"]["text_label"]["font_asset_id"],
                    color,
                    entity["components"]["text_label"]["fixed"].get_or(false)
                );
            }

            // Script
            sol::optional<sol::table> script = entity["components"]["on_update_script"];
            if (script != sol::nullopt) {
                sol::function func = entity["components"]["on_update_script"][0];
                newEntity.AddComponent<ScriptComponent>(func);
            }
        }
        i++;
    }
}