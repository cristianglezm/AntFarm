#include <SystemManager/SystemManager.hpp>

namespace ant{
    SystemManager::SystemManager(){}
    bool SystemManager::addSystem(std::shared_ptr<System> s){
        auto result = systems.insert(std::make_pair(s->getName(),s));
        return result.second;
    }
    std::shared_ptr<System> SystemManager::getSystem(const std::string& name){
        return systems[name];
    }
    void SystemManager::setSystems(container systems){
        this->systems = systems;
    }
    void SystemManager::removeSystem(const std::string& name){
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
    void SystemManager::render(sf::RenderWindow& win){
        for(auto& system : systems){
            system.second->render(win);
        }
    }
}
