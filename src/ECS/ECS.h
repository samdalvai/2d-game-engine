#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <set>

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
        Registry() = default;

        Entity CreateEntity();
        void AddEntityToSystem(Entity entity);

        template <typename T, typename ...TArgs> void AddComponent(Entity entity, TArgs&& ...args);
        template <typename T> void RemoveComponent(Entity entity);
        template <typename T> bool HasComponent(Entity entity);
        template <typename T> T& GetComponent(Entity entity);

        void Update();
};

template <typename TComponent>
void System::RequireComponent() {
    const auto componentId = Component<TComponent>::GetId();
    componentSignature.set(componentId);
}

#endif
