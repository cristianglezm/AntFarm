#include <SystemManager/SystemManager.hpp>

namespace ant{
    SystemManager::SystemManager(){

    }
    bool SystemManager::addSystem(std::shared_ptr<System> s){
        auto result = systems.insert(std::make_pair(s->getName(),s));
        return result.second;
    }
    std::shared_ptr<System> SystemManager::getSystem(std::string name){
        return systems.at(name);
    }
    void SystemManager::setSystems(std::map<std::string,std::shared_ptr<System>> systems){
        this->systems = systems;
    }
    std::map<std::string,std::shared_ptr<System>> SystemManager::getSystems(){
        return this->systems;
    }
    void SystemManager::removeSystem(std::string name){
        systems.erase(name);
    }
    void SystemManager::setEntityManager(std::shared_ptr<EntityManager> entityManager){
        for(auto& system : systems){
            system.second->setEntityManager(entityManager);
        }
    }
    void SystemManager::setEventQueue(std::shared_ptr<EventQueue> eventQueue){
        for(auto& system : systems){
            system.second->setEventQueue(eventQueue);
        }
    }
    void SystemManager::update(sf::Time dt){
        for(auto& system : systems){
            system.second->update(dt);
        }
    }
    void SystemManager::render(){
        for(auto& system : systems){
            system.second->render();
        }
    }
    SystemManager::~SystemManager(){

    }
}
