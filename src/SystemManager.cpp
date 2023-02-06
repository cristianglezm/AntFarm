#include <SystemManager.hpp>

namespace ant{
    bool SystemManager::addSystem(std::shared_ptr<System> s){
        systems.emplace_back(std::make_pair(s->getName(), s));
        return true;
    }
    std::shared_ptr<System> SystemManager::getSystem(const std::string& name){
        auto result = std::find_if(std::begin(systems), std::end(systems), 
	    [&](auto& pair){
                return pair.first == name;
        });
        return result->second;
    }
    void SystemManager::setSystems(container systems){
        this->systems = systems;
    }
    void SystemManager::removeSystem(const std::string& name){
        systems.erase(std::remove_if(std::begin(systems), std::end(systems), 
            [&](auto& pair){
                return pair.first == name;
        }), std::end(systems));
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
    void SystemManager::update(const sf::Time& dt){
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
