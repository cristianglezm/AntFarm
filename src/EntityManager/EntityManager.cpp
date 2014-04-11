#include <EntityManager/EntityManager.hpp>

namespace ant{
    EntityManager::EntityManager(){

    }
    void EntityManager::addEntity(std::unique_ptr<Entity> e){
        entities.push_back(std::move(e));
    }
    void EntityManager::removeEntity(std::unique_ptr<Entity>& e){
       entities.remove(std::move(e));
    }
    EntityManager::iterator EntityManager::removeEntity(const std::string& name){
        iterator i = entities.begin();
        while(i != entities.end()){
            if((*i).get()!=nullptr){
                if((*i)->getName() == name){
                    return entities.erase(i++);
                }
            }
            ++i;
        }
        return i;
    }
    EntityManager::iterator EntityManager::removeEntity(EntityManager::iterator it){
        return entities.erase(it);
    }
    Entity* EntityManager::getEntity(const std::string& name){
        for(auto& entity : entities){
            if(entity->getName() == name){
                return entity.get();
            }
        }
        return nullptr;
    }
    void EntityManager::addEntities(std::list<std::unique_ptr<Entity> > e){
        entities = std::move(e);
    }
    std::unique_ptr<Entity> EntityManager::Transfer(const std::string& name){
        std::unique_ptr<Entity> ne;
        for(auto& entity : entities){
            if(entity){
                if(entity->getName()== name){
                    ne = std::move(entity);
                    entities.remove(entity);
                    return std::move(ne);
                }
            }
        }
        return nullptr;
    }
    EntityManager::~EntityManager(){

    }
}
