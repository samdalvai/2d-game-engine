#ifndef ECS_H
#define ECS_H

#include "../Logger/Logger.h"

#include <bitset>
#include <vector>
#include <set>
#include <unordered_map>
#include <typeindex>

const unsigned int MAX_COMPONENTS = 32;

////////////////////////////////////////////////////////////////////////////////
// Signature
////////////////////////////////////////////////////////////////////////////////
// We use a bitset (1s and 0s) to keep track of which components an entity has,
// and also helps keep track of which entities a system is interested in.
////////////////////////////////////////////////////////////////////////////////
typedef std::bitset<MAX_COMPONENTS> Signature;

struct IComponent {
    protected:
        static int nextId;
};

// Used to assign a unique id to a component type
template <typename T>
class Component: public IComponent {
    // Returns the unique id of Component<T>
    static int GetId() {
        static auto id = nextId++;
        return id;
    }
};

class Entity {
    private:
        int id;

    public:
        Entity(int id): id(id) {};
        Entity(const Entity& entity) = default;
        int GetId() const;
        
        Entity& operator = (const Entity& other) = default;
        bool operator == (const Entity& other) const { return id == other.GetId(); }
        bool operator != (const Entity& other) const { return id != other.GetId(); }
        bool operator > (const Entity& other) const { return id > other.GetId(); }
        bool operator < (const Entity& other) const { return id < other.GetId(); }
};

////////////////////////////////////////////////////////////////////////////////
// System
////////////////////////////////////////////////////////////////////////////////
// The system processes entities that contain a specific signature
////////////////////////////////////////////////////////////////////////////////
class System {
    private:
        Signature componentSignature;
        std::vector<Entity> entities;

    public:
        System() = default;
        ~System() = default;
        
        void AddEntityToSystem(Entity entity);
        void RemoveEntityFromSystem(Entity entity);
        std::vector<Entity> GetSystemEntities() const;
        const Signature& GetComponentSignature() const;

        // Defines the component type that entities must have to be considered by the system
        template <typename TComponent> void RequireComponent();
};

class IPool {
    public:
        virtual ~IPool() {};
};

////////////////////////////////////////////////////////////////////////////////
// Pool
////////////////////////////////////////////////////////////////////////////////
// A pool is a vector that contains objects of type T
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class Pool: public IPool {
    private:
        std::vector<T> data;
    
    public:
        Pool(int size = 100) { data.resize(size); }
        ~Pool() = default;
    
        bool IsEmpty() const { 
            return data.empty(); 
        }
        
        bool GetSize() const {
            return data.size();
        }
        
        void Resize(int newSize) {
            data.resize(newSize);
        }

        void Clear() { 
            data.clear();
        }

        void Add(T object) {
            data.push_back(object);
        }

        void Set(int index, T object) {
            data[index] = object;
        }
        
        T& Get(int index) { 
            return static_cast<T&>(data[index]);
        }
        
        T& operator [](unsigned int index) {
            return data[index];
        }
};

////////////////////////////////////////////////////////////////////////////////
// Registry
////////////////////////////////////////////////////////////////////////////////
// Manages the creation and construction of entities, components and systems
////////////////////////////////////////////////////////////////////////////////
class Registry {
    private:
        int numOfEntities = 0;

        // Vector of component pools, each pool contains all the data for a component type
        // [Vector index = component type id]
        // [Pool index = entity id]
        std::vector<IPool*> componentPools;

        // Vector of component signatures
        // The signature lets us know which components are turned "on" for an entity
        // [vector index = entity id]
        std::vector<Signature> entityComponentSignatures;

        // Map of active systems [index = system type id]
        std::unordered_map<std::type_index, System*> systems;

        std::set<Entity> entitiesToBeAdded;
        std::set<Entity> entitiesToBeKilled;

    public:
        Registry() {
            Logger::Log("Registry constructor called");
        };
        ~Registry() {
            Logger::Log("Registry destructor called");
        }

        Entity CreateEntity();
        void AddEntityToSystems(Entity entity);

        // Component management
        template <typename TComponent, typename ...TArgs> void AddComponent(Entity entity, TArgs&& ...args);
        template <typename TComponent> void RemoveComponent(Entity entity);
        template <typename TComponent> bool HasComponent(Entity entity) const;
        template <typename TComponent> TComponent& GetComponent(Entity entity) const;

        // System management
        template <typename TSystem, typename ...TArgs> void AddSystem(TArgs&& ...args);
        template <typename TSystem> void RemoveSystem();
        template <typename TSystem> bool HasSystem() const;
        template <typename TSystem> TSystem& GetSystem() const;

        void Update();
};

template <typename TComponent>
void System::RequireComponent() {
    const auto componentId = Component<TComponent>::GetId();
    componentSignature.set(componentId);
}

template <typename TComponent, typename ...TArgs> 
void Registry::AddComponent(Entity entity, TArgs&& ...args) {
    const auto componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();

    if (componentId >= componentPools.size()) {
        componentPools.resize(entityId + 1, nullptr);
    }

    if (!componentPools[componentId]) {
        // TODO: use smart pointer here
        Pool<TComponent>* newComponentPool = new Pool<TComponent>();
        componentPools[componentId] = newComponentPool;
    }

    Pool<TComponent>* componentPool = componentPools[componentId];

    // TODO: what if we delete an entity? Will the component pool size remain the same?
    // The id of the entities des not go back
    if (entityId >= componentPool->GetSize()) {
        componentPool->Resize(numOfEntities);
    }

    TComponent newComponent(std::forward<TArgs>(args)...);

    componentPool->Set(entityId, newComponent);
    entityComponentSignatures[entityId].set(componentId);
};

template <typename TComponent> 
void Registry::RemoveComponent(Entity entity) {
    const auto componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();

    entityComponentSignatures[entityId].set(componentId, false);
}

template <typename TComponent>
bool Registry::HasComponent(Entity entity) const {
    const auto componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();

    return entityComponentSignatures[entityId].test(componentId);
}

template <typename TComponent> 
TComponent& Registry::GetComponent(Entity entity) const {
    //TODO...
}

template <typename TSystem, typename ...TArgs>
void Registry::AddSystem(TArgs&& ...args) {
    // TODO: use smart pointer here
    TSystem* newSystem(new System(std::forward<TArgs>(args)...));
    systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

template <typename TSystem>
void Registry::RemoveSystem() {
    auto system = systems.find(std::type_index(typeid(TSystem)));
    systems.erase(system);
}

template <typename TSystem>
bool Registry::HasSystem() const {
    return systems.find(std::type_index(typeid(TSystem))) != systems.end();
}

template <typename TSystem>
TSystem& Registry::GetSystem() const {
    auto system = systems.find(std::type_index(typeid(TSystem)));
    return *(std::static_pointer_cast<TSystem>(system->second));
}

#endif
