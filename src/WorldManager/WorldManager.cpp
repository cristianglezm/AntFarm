#include <WorldManager/WorldManager.hpp>
#include <iostream>
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
    void WorldManager::update(long int id,sf::Time dt){
        if(id==-1){
            for(auto& world:worlds){
                world.second->update(dt);
            }
        }else{
            worlds.at(id)->update(dt);
        }
    }
    void WorldManager::render(long int id,sf::RenderWindow& win){
        if(id==-1){
            for(auto& world:worlds){
                world.second->render(win);
            }
        }else{
            worlds.at(id)->render(win);
        }
    }
    WorldManager::~WorldManager(){

    }
}
