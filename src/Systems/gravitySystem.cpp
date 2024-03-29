#include <Systems/gravitySystem.hpp>

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
    void gravitySystem::update([[maybe_unused]] const sf::Time& dt){
        for(auto& e : em->getEntities()){
            if(e->hasComponent(RequiredComponents) && e->is(States::FALLING)){
                auto& properties = e->getComponent(RequiredComponents)
                                    ->getProperties<ComponentsAlias::velocity>();
                std::get<0>(properties).y = Gravity;
            }
        }
    }
    void gravitySystem::render([[maybe_unused]] sf::RenderWindow& win){
        return;
    }
}
