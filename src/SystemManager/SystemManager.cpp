#include <SystemManager/SystemManager.hpp>

namespace ant{
    SystemManager::SystemManager(){

    }
    bool SystemManager::addSystem(std::shared_ptr<System> s){
        auto result = systems.insert(std::make_pair(s->getName(),s);
        return result.second;
    }
    shared_ptr<System> SystemManager::getSystem(std::string name){
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
    SystemManager::~SystemManager(){

    }
}
