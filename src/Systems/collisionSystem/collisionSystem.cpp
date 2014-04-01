#include <Systems/collisionSystem/collisionSystem.hpp>

namespace ant{
    collisionSystem::collisionSystem(long int req,sf::FloatRect bounds):qtree(bounds),System(req){
        name = "collisionSystem";
    }
    void collisionSystem::render(sf::RenderWindow& win){
        return;
    }
    void collisionSystem::update(sf::Time dt){
        qtree.clear();
        for(auto& entity: em->getEntities()){
            if((entity->getMask() & RequiredComponents) == RequiredComponents){
                auto& bounds = std::get<0>(entity->getComponent(ComponentsMask::COMPONENT_BOUNDS)->getProperties<sf::FloatRect>());
                auto& transf = std::get<0>(entity->getComponent(ComponentsMask::COMPONENT_TRANSFORM)->getProperties<sf::Vector2f,sf::Vector2f,float>());
                bounds.left = transf.x;
                bounds.top = transf.y;
                qtree.insert(entity.get());
            }
        }
        Utils::Quadtree::list entities;
        for(auto& entity1: em->getEntities()){
            entities.clear();
            qtree.retrieve(entities,entity1.get());
            for(auto entity2:entities){
                        auto& properties1 = entity1->getComponent(ComponentsMask::COMPONENT_BOUNDS)->getProperties<sf::FloatRect>();
                        sf::FloatRect eBounds1 = std::get<0>(properties1);
                        auto& properties2 = entity2->getComponent(ComponentsMask::COMPONENT_BOUNDS)->getProperties<sf::FloatRect>();
                        sf::FloatRect eBounds2 = std::get<0>(properties2);
                        if(eBounds1.intersects(eBounds2)){
                            eventQueue->push(std::shared_ptr<baseEvent>(new Event<Entity*,Entity*>(EventType::COLLISION_EVENT,entity1.get(),entity2)));
                        }
                    }
        }
    }
    collisionSystem::~collisionSystem(){

    }
}
