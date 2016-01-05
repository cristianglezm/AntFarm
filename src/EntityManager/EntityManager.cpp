#include <EntityManager/EntityManager.hpp>

namespace ant{

    void EntityManager::addEntity(std::unique_ptr<Entity> e){
        entities.emplace_back(std::move(e));
    }
    EntityManager::iterator EntityManager::removeEntity(const std::string& name){
        return entities.erase(std::remove_if(entities.begin(),entities.end(),
                    [&](const std::unique_ptr<Entity>& e){return (e->getName() == name);}),
                    entities.end());
    }
    EntityManager::iterator EntityManager::removeEntity(EntityManager::iterator it){
        return entities.erase(it);
    }
    Entity* EntityManager::getEntity(const std::string& name){
        auto found = std::find_if(entities.begin(),entities.end(),
                    [&](std::unique_ptr<Entity>& e){ return (e->getName() == name); });
        if(found != entities.end()){
            return found->get();
        }
        return nullptr;
    }
    void EntityManager::addEntities(container&& e){
        entities = std::move(e);
    }
    std::unique_ptr<Entity> EntityManager::Transfer(const std::string& name){
        std::unique_ptr<Entity> ne;
        auto it = std::find_if(entities.begin(),entities.end(),
                [&](std::unique_ptr<Entity>& e){ return (e->getName() == name); });
        if(it != entities.end()){
            ne = std::move(*it);
            entities.erase(it);
            return std::move(ne);
        }
        return std::unique_ptr<Entity>();
    }
    std::unique_ptr<Entity> EntityManager::Transfer(const Entity* e){
        std::unique_ptr<Entity> ne;
        auto it = std::find_if(entities.begin(),entities.end(),
                [&](std::unique_ptr<Entity>& entity){ return (entity.get() == e); });
        if(it != entities.end()){
            ne = std::move(*it);
            entities.erase(it);
            return std::move(ne);
        }
        return std::unique_ptr<Entity>();
    }
}
