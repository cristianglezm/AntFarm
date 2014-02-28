#include <EntityManager/EntityManager.hpp>
namespace ant{
    EntityManager::EntityManager(){
        entities = std::vector<Entity>();
    }
    void EntityManager::addEntity(Entity e){
        entities.push_back(e);
    }
    void EntityManager::removeEntity(Entity e){
       entities.erase(std::remove(entities.begin(), entities.end(), e),entities.end());
    }
    Entity EntityManager::getEntity(std::string name){
        Entity e;
        for(auto& entity:entities){
            if(entity.getName() == name){
                e = entity;
            }
        }
        return e;
    }
    void EntityManager::addEntities(std::vector<Entity> e){
        entities = e;
    }
    EntityManager::~EntityManager(){

    }
}
