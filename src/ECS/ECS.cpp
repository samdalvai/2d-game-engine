#include "ECS.h"
#include "../Logger/Logger.h"

int Entity::GetId() const {
    return id;
}

void System::AddEntityToSystem(Entity entity) {
    entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity) {
    int entityPosition = -1;

    for (int i = 0; i < entities.size(); i++) {
        if (entities[i].GetId() == entity.GetId()) {
            entityPosition = i;
            break;
        }
    }

    if (entityPosition != -1) {
        entities.erase(entities.begin() + entityPosition);
    } else {
        Logger::Err("Failed to delete entity with id: " + entity.GetId());
    }
}

std::vector<Entity> System::GetSystemEntities() const {
    return entities;
}

const Signature& System::GetComponentSignature() const {
    return componentSignature;
}