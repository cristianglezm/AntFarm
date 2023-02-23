#include <Systems/movementSystem.hpp>
#include <Event/EventsAlias.hpp>

namespace ant{
    movementSystem::movementSystem(){
        name="movementSystem";
        RequiredComponents =  ComponentsMask::COMPONENT_TRANSFORM | ComponentsMask::COMPONENT_VELOCITY;
    }
    void movementSystem::onNotify(std::shared_ptr<baseEvent> e){
        switch(e->getType()){
            case EventType::TERRAIN_COLLISION:{
                static const int UP = 180;
                static const int LEFT = -90;
                static const int RIGHT = 90;
                auto& attributes = e->getAttributes<EventsAlias::terrain_collision>();
                auto& entity = std::get<0>(attributes);
                auto& type = std::get<1>(attributes);
                if(entity->hasComponent(ComponentsMask::COMPONENT_TRANSFORM | ComponentsMask::COMPONENT_BOUNDS)){
                    auto component = entity->getComponent(ComponentsMask::COMPONENT_TRANSFORM);
                    if(component){
                        auto& properties = component->getProperties<ComponentsAlias::transform>();
                        auto& rotation = std::get<2>(properties);
                        auto& position = std::get<0>(properties);
                        switch(type){
                            case 0:
                                if(entity->is(States::CLIMBING)){
                                    rotation = UP;
                                }else{
                                    rotation = LEFT;
                                }
                            break;
                            case 1:
                                if(entity->is(States::CLIMBING)){
                                    rotation = UP;
                                }else{
                                    rotation = RIGHT;
                                }
                            break;
                            case 2:{
                                auto& cBounds = entity->getComponent(ComponentsMask::COMPONENT_BOUNDS)
                                                            ->getProperties<ComponentsAlias::bounds>();
                                auto& bounds = std::get<0>(cBounds);
                                // climbing stairs
                                position.y -= (bounds.height / 2.0);
                            }
                            break;
                            case 3:
                                if(rotation == UP){
                                    rotation = RIGHT;
                                }
                            break;
                            case 4:
                                if(rotation == UP){
                                    rotation = LEFT;
                                }
                            break;
                        }
                    }
                }
            }
            break;
        }
    }
    void movementSystem::render([[maybe_unused]] sf::RenderWindow& win){
        return;
    }
    void movementSystem::update([[maybe_unused]] const sf::Time& dt){
        for(auto& entity: em->getEntities()){
            if(entity->hasComponent(RequiredComponents)){
                auto& transf = entity->getComponent(ComponentsMask::COMPONENT_TRANSFORM)
                                        ->getProperties<ComponentsAlias::transform>();
                auto& velocity = entity->getComponent(ComponentsMask::COMPONENT_VELOCITY)
                                        ->getProperties<ComponentsAlias::velocity>();
                if(entity->is(States::GROUND)){
                    std::get<0>(velocity) = sf::Vector2f(std::get<1>(velocity) *  -std::sin(Utils::toRadians<float>(std::get<2>(transf))) ,
                                                         std::get<1>(velocity) *  std::cos(Utils::toRadians<float>(std::get<2>(transf))) );
                }
                std::get<0>(transf) += std::get<0>(velocity);
            }
        }
    }
}
