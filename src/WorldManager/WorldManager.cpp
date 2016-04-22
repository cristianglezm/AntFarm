#include <WorldManager/WorldManager.hpp>

namespace ant{
    WorldManager::WorldManager(){}
    void WorldManager::addWorld(std::unique_ptr<World> w){
        worlds.insert(std::make_pair(w->getId(),std::move(w)));
    }
    World* WorldManager::getWorld(int id){
        return worlds.at(id).get();
    }
    void WorldManager::removeWorld(int id){
        worlds.erase(id);
    }
    void WorldManager::setWorlds(std::map<int,std::unique_ptr<World>> worlds){
        this->worlds = std::move(worlds);
    }
    void WorldManager::update(int id,sf::Time dt){
        if(id==-1){
            for(auto& world:worlds){
                world.second->update(dt);
            }
        }else{
            worlds.at(id)->update(dt);
        }
    }
    void WorldManager::render(int id, sf::RenderWindow& win){
        if(id==-1){
            for(auto& world:worlds){
                world.second->render(win);
            }
        }else{
            worlds.at(id)->render(win);
        }
    }
    void WorldManager::clear(){
        worlds.clear();
    }
}
