#include <EntityManager/EntityManager.hpp>
namespace ant{
    EntityManager::EntityManager(){

    }
    void EntityManager::addEntity(std::unique_ptr<Entity> e){
        entities.push_back(std::move(e));
    }
    void EntityManager::removeEntity(std::unique_ptr<Entity> e){
       entities.remove(std::move(e));
    }
    void EntityManager::removeEntity(std::string name){
        for(auto& entity:entities){
            if(entity->getName()==name){
                entities.remove(entity);
            }
        }
    }
    std::unique_ptr<Entity>& EntityManager::getEntity(std::string name){
        for(auto& entity : entities){
            if(entity->getName() == name){
                return entity;
            }
        }
    }
    void EntityManager::addEntities(std::list<std::unique_ptr<Entity> > e){
        entities = std::move(e);
    }
    std::unique_ptr<Entity> EntityManager::Transfer(std::string name){
        std::unique_ptr<Entity> ne;
        /// FIX THIS SHIT
        for(auto& entity : entities){
            if(entity!=nullptr){
                if(entity->getName()== name){
                    ne = std::move(entity);
                    entities.remove(entity);
                }
            }
        }
        return std::move(ne);
    }
    EntityManager::~EntityManager(){

    }
}
