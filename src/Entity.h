#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <map>
#include "./EntityManager.h"
#include "./Component.h"

class Component;
class EntityManager;

class Entity {
    private:
        EntityManager& manager;
        bool isActive;
        std::vector<Component*> components;
        std:map<const std::type_info*, Component*> componentTypeMap;

    public:
        std::string name; //Move this to a ui32 hash
        Entity(EntityManager& manager);
        Entity(EntityManager& manager, std::string name);
        void Update(float deltaTime);
        void Render();
        void Destroy();
        bool IsActive() const;

        //This adds components to the entity;
        template <typename T, typename... TArgs>
        T& Addcomponent(TArgs&&... args){
            T* newComponent(new T(std::forward<TArgs>(args)...));

            newComponent->owner = this;
            components.emplace_back(newComponent);
            componentTypeMap[&typeid(*newComponent)] = newComponent;
            newComponent->Initialize();
            return *newComponent;
        }

        //Returns a sprite component
        template <typename T>
        T* GetComponent(){
            return static_cast<T*>(componentTypeMap[&typeid(T)]);
        }

};

#endif