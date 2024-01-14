#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/HealthComponent.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"

class DamageSystem: public System {
    public:
        DamageSystem() {
            RequireComponent<BoxColliderComponent>();
        }

        void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
            eventBus->SubscribeToEvent<CollisionEvent>(this, &DamageSystem::OnCollision);
        }

        void OnCollision(CollisionEvent& event) {
            Entity a = event.a;
            Entity b = event.b;
            Logger::Log("Collision event emitted: " + std::to_string(a.GetId()) + " and " + std::to_string(b.GetId()));
        
            if (a.BelongsToGroup("projectiles") && b.HasTag("player")) {
                OnProjectileHitsPlayer(a, b); // "a" is the projectile, "b" is the player
            }

            if (b.BelongsToGroup("projectiles") && a.HasTag("player")) {
                OnProjectileHitsPlayer(b, a); // "b" is the projectile, "a" is the player
            }

            if (a.BelongsToGroup("projectiles") && b.BelongsToGroup("enemies")) {
                OnProjectileHitsEnemy(a, b);
            }
            
            if (b.BelongsToGroup("projectiles") && a.BelongsToGroup("enemies")) {
                OnProjectileHitsEnemy(b, a);
            }
        }

        void OnProjectileHitsPlayer(Entity projectile, Entity player) {
            const auto projectileComponent = projectile.GetComponent<ProjectileComponent>();

            if (!projectileComponent.isFriendly) {
                HitEntityWithProjectile(player, projectile, projectileComponent);
            }
        }

        void OnProjectileHitsEnemy(Entity projectile, Entity enemy) {
            const auto projectileComponent = projectile.GetComponent<ProjectileComponent>();

            if (projectileComponent.isFriendly) {
                HitEntityWithProjectile(enemy, projectile, projectileComponent);
            }
        }

        void HitEntityWithProjectile(Entity entity, Entity projectile, const ProjectileComponent projectileComponent) {
            auto& health = entity.GetComponent<HealthComponent>();

            health.healthPercentage -= projectileComponent.hitPercentDamage;

            Logger::Log("Projectile hit, entity remaining entity health: " + std::to_string(health.healthPercentage) + " %");

            if (health.healthPercentage <= 0) {
                entity.Kill();
            }

            projectile.Kill();
        }
};

#endif
