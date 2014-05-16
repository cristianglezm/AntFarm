#include <Systems/movementSystem/movementSystem.hpp>

namespace ant{
    movementSystem::movementSystem(){
        name="movementSystem";
        RequiredComponents =  ComponentsMask::COMPONENT_TRANSFORM | ComponentsMask::COMPONENT_VELOCITY;
    }
    void movementSystem::onNotify(std::shared_ptr<baseEvent> e){
        switch(e->getType()){
            case EventType::COLLISION_EVENT:{
                    auto& attributes = e->getAttributes<Entity*,Entity*>();
                    // obtenemos los atributos del evento.
                    auto& entity1 = std::get<0>(attributes);
                    auto& entity2 = std::get<1>(attributes);
                    if(entity1->hasComponent(ComponentsMask::COMPONENT_VELOCITY)){
                        auto& velocity1 = entity1->getComponent(ComponentsMask::COMPONENT_VELOCITY)
                                                    ->getProperties<sf::Vector2f,float,float,float>();
                        //std::get<1>(velocity1) = 0;
                    }
                    if(entity2->hasComponent(ComponentsMask::COMPONENT_VELOCITY)){
                        auto& velocity2 = entity2->getComponent(ComponentsMask::COMPONENT_VELOCITY)
                                                    ->getProperties<sf::Vector2f,float,float,float>();
                        //std::get<1>(velocity2) = 0;
                    }
            }
                break;
            case EventType::TERRAIN_COLLISION:{
                auto& attributes = e->getAttributes<Entity*,int>();
                auto& entity = std::get<0>(attributes);
                auto& type = std::get<1>(attributes);
                if(entity->hasComponent(ComponentsMask::COMPONENT_TRANSFORM)){
                    auto& properties = entity->getComponent(ComponentsMask::COMPONENT_TRANSFORM)
                                                 ->getProperties<sf::Vector2f,sf::Vector2f,float>();
                    auto& rotation = std::get<2>(properties);
                    auto& position = std::get<0>(properties);
                    switch(type){
                        case 0:
                            if(entity->is(States::CLIMBING)){
                                rotation = 180;
                            }else{
                                rotation = -90;
                            }
                            break;
                        case 1:
                            if(entity->is(States::CLIMBING)){
                                rotation = 180;
                            }else{
                                rotation = 90;
                            }
                            break;
                        case 2:
                            // subir escaleras
                            position.y -=5;
                            break;
                        case 3:
                            if(rotation == 180){
                                rotation = 90;
                            }
                            break;
                        case 4:
                            if(rotation == 180){
                                rotation = -90;
                            }
                            break;
                    }
                }
            }
                break;
        }
    }
    void movementSystem::render(sf::RenderWindow& win){
        return;
    }
    void movementSystem::update(sf::Time dt){
        for(auto& entity: em->getEntities()){
            if(entity->hasComponent(RequiredComponents)){
                auto& transf = entity->getComponent(ComponentsMask::COMPONENT_TRANSFORM)
                                        ->getProperties<sf::Vector2f,sf::Vector2f,float>();
                auto& velocity = entity->getComponent(ComponentsMask::COMPONENT_VELOCITY)
                                        ->getProperties<sf::Vector2f,float,float,float>();
                if(entity->is(States::GROUND)){
                    std::get<0>(velocity) = sf::Vector2f(std::get<1>(velocity) *  -std::sin(Utils::toRadians<float>(std::get<2>(transf))) ,
                                                         std::get<1>(velocity) *  std::cos(Utils::toRadians<float>(std::get<2>(transf))) );
                /// @todo agregar al calculo delta time
                }
                std::get<0>(transf) += std::get<0>(velocity);
            }
        }
    }
    movementSystem::~movementSystem(){

    }
}
