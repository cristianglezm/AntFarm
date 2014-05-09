#include <Systems/collisionSystem/collisionSystem.hpp>

namespace ant{
    collisionSystem::collisionSystem(sf::FloatRect bounds,sf::VertexArray* GameMap)
    :qtree(bounds)
    ,gameBounds(bounds)
    ,gameMap(GameMap){
        name = "collisionSystem";
        RequiredComponents = ComponentsMask::COMPONENT_TRANSFORM | ComponentsMask::COMPONENT_BOUNDS;
    }
    void collisionSystem::update(sf::Time dt){
        qtree.clear();
        for(auto& entity: em->getEntities()){
            if((entity->hasComponent(RequiredComponents))){
                auto& cBounds = entity->getComponent(ComponentsMask::COMPONENT_BOUNDS)
                                ->getProperties<sf::FloatRect>();
                auto& bounds = std::get<0>(cBounds);
                auto& cTransf = entity->getComponent(ComponentsMask::COMPONENT_TRANSFORM)
                                ->getProperties<sf::Vector2f,sf::Vector2f,float>();
                auto& pos = std::get<0>(cTransf);
                bounds.left = pos.x;
                bounds.top = pos.y;
                auto& rotation = std::get<2>(cTransf);
                ///  @todo rotation of boundingbox
                //bounds = Utils::rotateRect(bounds,rotation);
                qtree.insert(entity.get());
            }
        }
        Utils::Quadtree::list entities;
        for(auto& entity1: em->getEntities()){
            entities.clear();
            if((entity1->hasComponent(RequiredComponents))){
                qtree.retrieve(entities,entity1.get());
                for(auto entity2:entities){
                    auto& properties1 = entity1->getComponent(ComponentsMask::COMPONENT_BOUNDS)
                                            ->getProperties<sf::FloatRect>();
                    auto& eBounds1 = std::get<0>(properties1);
                    if(entity1.get()!=entity2){
                        auto& properties2 = entity2->getComponent(ComponentsMask::COMPONENT_BOUNDS)
                                            ->getProperties<sf::FloatRect>();
                        auto& eBounds2 = std::get<0>(properties2);
                        if(eBounds1.intersects(eBounds2)){
                            eventQueue->push(std::shared_ptr<baseEvent>(new Event<Entity*,Entity*>(
                                                EventType::COLLISION_EVENT,entity1.get(),entity2)));
                        }/// @todo Arreglar colision con 4 puntos y hacer funcion para comprobar.
                        if((*gameMap)[((int)gameBounds.height) * ((int)eBounds2.left) + ((int)eBounds2.top)].color.a == 255
                           || (*gameMap)[((int)gameBounds.height) * ((int)(eBounds2.left+eBounds2.width)) + ((int)eBounds2.top)].color.a == 255
                           || (*gameMap)[((int)gameBounds.height) * ((int)eBounds2.left) + ((int)(eBounds2.top+eBounds2.height))].color.a == 255
                           || (*gameMap)[((int)gameBounds.height) * ((int)(eBounds2.left+eBounds2.width)) + ((int)(eBounds2.top+eBounds2.height))].color.a == 255){
                                entity2->addState(States::GROUND);
                                entity2->removeState(States::FALLING);
                        }else{
                            entity2->removeState(States::GROUND);
                            entity2->addState(States::FALLING);
                        }
                    }
                }
            }
        }
    }
    collisionSystem::~collisionSystem(){

    }
}
