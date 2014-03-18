#include <WorldManager/WorldManager.hpp>

namespace ant{
    WorldManager::WorldManager(){

    }
    void WorldManager::addWorld(std::unique_ptr<World> w){

    }
    World* WorldManager::getWorld(std::string id){

    }
    bool WorldManager::removeWorld(std::string id){

    }
    void WorldManager::setWorlds(std::map<std::string,std::unique_ptr<World>> worlds){
        this->worlds = std::move(worlds);
    }
    WorldManager::~WorldManager(){

    }
};
