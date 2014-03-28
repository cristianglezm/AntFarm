#include <Systems/collisionSystem/collisionSystem.hpp>

namespace ant{
    collisionSystem::collisionSystem(long int req,sf::FloatRect bounds):qtree(bounds,System(req)){
        name = "collisionSystem";
    }
    void collisionSystem::render(sf::RenderWindow& win){
        return;
    }
    void collisionSystem::update(sf::Time dt){
        qtree.clear();
        for(auto& entity: em->getEntities()){
            qtree.insert(entity.get());
        }

    }
    collisionSystem::~collisionSystem(){

    }
}
