#include <WorldManager/WorldManager.hpp>

namespace ant{
    WorldManager::WorldManager(){

    }
    void WorldManager::addWorld(std::unique_ptr<World> w){
        worlds.insert(std::make_pair(w->getId(),std::move(w)));
    }
    World* WorldManager::getWorld(long int id){
        return worlds.at(id).get();
    }
    void WorldManager::removeWorld(long int id){
        worlds.erase(id);
    }
    void WorldManager::setWorlds(std::map<long int,std::unique_ptr<World>> worlds){
        this->worlds = std::move(worlds);
    }
    void WorldManager::update(sf::Time dt){
        for(auto& world:worlds){
            world.second->update(dt);
        }
    }
    void WorldManager::render(){
        for(auto& world:worlds){
            world.second->render();
        }
    }
    WorldManager::~WorldManager(){

    }
};
