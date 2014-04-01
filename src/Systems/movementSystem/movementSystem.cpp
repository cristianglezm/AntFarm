#include <Systems/movementSystem/movementSystem.hpp>

namespace ant{
    movementSystem::movementSystem(){
        name="movementSystem";
        RequiredComponents =  ComponentsMask::COMPONENT_TRANSFORM | ComponentsMask::COMPONENT_VELOCITY;
    }
    void movementSystem::onNotify(std::shared_ptr<baseEvent> e){
        switch(e->getType()){
            case EventType::COLLISION_EVENT:
                    auto& attributes = e->getAttributes<Entity*,Entity*>();
                    auto& entity1 = std::get<0>(attributes);
                    auto& entity2 = std::get<1>(attributes);
                    if((entity1->getMask() & ComponentsMask::COMPONENT_VELOCITY) == ComponentsMask::COMPONENT_VELOCITY){
                        auto& velocity1 = entity1->getComponent(ComponentsMask::COMPONENT_VELOCITY)->getProperties<sf::Vector2f,float,float,float>();
                        std::get<1>(velocity1) = 0;
                    }
                    if((entity2->getMask() & ComponentsMask::COMPONENT_VELOCITY) == ComponentsMask::COMPONENT_VELOCITY){
                        auto& velocity2 = entity2->getComponent(ComponentsMask::COMPONENT_VELOCITY)->getProperties<sf::Vector2f,float,float,float>();
                        std::get<1>(velocity2) = 0;
                    }
                break;
        }
    }
    void movementSystem::render(sf::RenderWindow& win){
        return;
    }
    void movementSystem::update(sf::Time dt){
        for(auto& entity: em->getEntities()){
            if((entity->getMask() & RequiredComponents) == RequiredComponents){
                auto& transf = entity->getComponent(ComponentsMask::COMPONENT_TRANSFORM)->getProperties<sf::Vector2f,sf::Vector2f,float>();
                auto& velocity = entity->getComponent(ComponentsMask::COMPONENT_VELOCITY)->getProperties<sf::Vector2f,float,float,float>();
                std::get<0>(velocity) = sf::Vector2f(std::get<1>(velocity) *  std::sin(std::get<2>(transf)),
                                                     std::get<1>(velocity) *  std::cos(std::get<2>(transf)));
                                                     /// TODO agregar al calculo delta time
                                                     /// Arreglar problema de sin,cos y direccion de movimiento.
                std::get<0>(transf) += std::get<0>(velocity);
            }
        }
    }
    movementSystem::~movementSystem(){

    }
}
