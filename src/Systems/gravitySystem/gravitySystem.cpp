#include <Systems/gravitySystem/gravitySystem.hpp>

namespace ant{
    gravitySystem::gravitySystem(){
        Gravity = 0.8;
        name = "gravitySystem";
        RequiredComponents = ComponentsMask::COMPONENT_VELOCITY;
    }
    gravitySystem::gravitySystem(float g){
        Gravity = g;
        name = "gravitySystem";
        RequiredComponents = ComponentsMask::COMPONENT_VELOCITY;
    }
    void gravitySystem::setGravity(float g){
        Gravity = g;
    }
    void gravitySystem::update(sf::Time dt){
        for(auto& e : em->getEntities()){
            if(e->hasComponent(RequiredComponents) && e->is(States::FALLING)){
                auto& properties = e->getComponent(RequiredComponents)
                                    ->getProperties<sf::Vector2f,float,float,float>();
                std::get<0>(properties).y = Gravity ;
            }
        }
    }
    void gravitySystem::render(sf::RenderWindow& win){
        return;
    }
    gravitySystem::~gravitySystem(){

    }
}
