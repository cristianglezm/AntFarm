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
        return entities.erase(std::remove_if(entities.begin(),entities.end(),
                    [&](const std::unique_ptr<Entity>& e){
                                      return (e->getName() == name);
                                      }));
    }
    EntityManager::iterator EntityManager::removeEntity(EntityManager::iterator it){
        return entities.erase(it);
    }
    Entity* EntityManager::getEntity(const std::string& name){
        return (*std::find_if(entities.begin(),entities.end(),[&](std::unique_ptr<Entity>& e){
                            return (e->getName() == name);
                            })).get();
    }
    void EntityManager::addEntities(std::list<std::unique_ptr<Entity> > e){
        entities = std::move(e);
    }
    std::unique_ptr<Entity> EntityManager::Transfer(const std::string& name){
        std::unique_ptr<Entity> ne;
        auto it = std::find_if(entities.begin(),entities.end(),
                [&](std::unique_ptr<Entity>& e){
                     return (e->getName() == name);
                     });
        ne = std::move(*it);
        entities.erase(it);
        return std::move(ne);
    }
    std::unique_ptr<Entity> EntityManager::Transfer(const Entity* e){
        std::unique_ptr<Entity> ne;
        auto it = std::find_if(entities.begin(),entities.end(),
                [&](std::unique_ptr<Entity>& entity){
                     return (entity.get() == e);
                     });
        ne = std::move(*it);
        entities.erase(it);
        return std::move(ne);
    }
    EntityManager::~EntityManager(){

    }
}
