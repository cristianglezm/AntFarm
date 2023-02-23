#include <Systems/collisionSystem.hpp>
#include <Event/EventsAlias.hpp>

namespace ant{
    collisionSystem::collisionSystem(sf::FloatRect bounds,sf::VertexArray* GameMap)
    : qtree(bounds)
    , gameBounds(bounds)
    , gameMap(GameMap){
        name = "collisionSystem";
        RequiredComponents = ComponentsMask::COMPONENT_TRANSFORM | ComponentsMask::COMPONENT_BOUNDS;
    }
    void collisionSystem::update([[maybe_unused]] const sf::Time& dt){
        qtree.clear();
        for(auto& entity: em->getEntities()){
            if((entity->hasComponent(RequiredComponents))){
                auto& cBounds = entity->getComponent(ComponentsMask::COMPONENT_BOUNDS)
                                ->getProperties<ComponentsAlias::bounds>();
                auto& bounds = std::get<0>(cBounds);
                auto& cTransf = entity->getComponent(ComponentsMask::COMPONENT_TRANSFORM)
                                ->getProperties<ComponentsAlias::transform>();
                auto& pos = std::get<0>(cTransf);
                bounds.left = pos.x;
                bounds.top = pos.y;
                qtree.insert(entity.get());
            }
        }
        Utils::Quadtree::list entities;
        for(auto& entity1: em->getEntities()){
            entities.clear();
            if(entity1->hasComponent(RequiredComponents)){
                qtree.retrieve(entities,entity1.get());
                auto& properties1 = entity1->getComponent(ComponentsMask::COMPONENT_BOUNDS)
                                            ->getProperties<ComponentsAlias::bounds>();
                auto& eBounds1 = std::get<0>(properties1);
                if(!Utils::RectContains(eBounds1,gameBounds)){
                    eventQueue->push(std::make_shared<EventsAlias::out_map>(EventType::OUT_MAP,entity1.get()));
                }else{
                    testTerrainCollision(entity1.get(),eBounds1);
                }
                for(auto entity2:entities){
                    if(entity1.get() != entity2){
                        auto& properties2 = entity2->getComponent(ComponentsMask::COMPONENT_BOUNDS)
                                                    ->getProperties<ComponentsAlias::bounds>();
                        auto& eBounds2 = std::get<0>(properties2);
                        if(eBounds1.intersects(eBounds2)){
                            eventQueue->push(std::make_shared<EventsAlias::collision>(EventType::COLLISION_EVENT,entity1.get(),entity2));
                        }
                    }
                }
            }
        }
    }
    void collisionSystem::testTerrainCollision(Entity* entity,const sf::FloatRect& eBounds){
        /*
         * check collisions 
         * 1 check left wall -> sends terrain_collision Event with 0 to turn right
         * 2 check right wall -> sends terrain_collision Event with 1 to turn left
         * 3 check left stairs -> sends terrain_collision Event with 2 for stairs
         * 4 check right stairs -> sends terrain_collision Event with 2 for stairs
         * 5 check bottom left -> changes status from FALLING to GROUND
         * 6 check bottom right -> changes status from FALLING to GROUND
         */
        int gbHeight = static_cast<int>(gameBounds.height);
        sf::IntRect bounds(eBounds.left, eBounds.top, eBounds.width, eBounds.height);
        if(isGround(topLeft(gbHeight, bounds)) && 
           isGround(middleLeft(gbHeight, bounds)) && 
           isGround(bottomLeft(gbHeight, bounds))){
            // check left wall
            eventQueue->push(std::make_shared<EventsAlias::terrain_collision>(EventType::TERRAIN_COLLISION,entity,0));
        }else if(isGround(topRight(gbHeight, bounds)) && 
                 isGround(middleRight(gbHeight, bounds)) && 
                 isGround(bottomRight(gbHeight, bounds))){
            // check right wall 
            eventQueue->push(std::make_shared<EventsAlias::terrain_collision>(EventType::TERRAIN_COLLISION,entity,1));
        }else if(! isGround(topLeft(gbHeight, bounds)) && 
                   isGround(middleLeft(gbHeight, bounds, 15)) && 
                   isGround(bottomLeft(gbHeight, bounds))){
            // send event for stairs
            eventQueue->push(std::make_shared<EventsAlias::terrain_collision>(EventType::TERRAIN_COLLISION,entity,2));
        }else if(! isGround(topRight(gbHeight, bounds)) && 
                   isGround(middleRight(gbHeight, bounds, 15)) && 
                   isGround(bottomRight(gbHeight, bounds))){
            // send event for stairs
            eventQueue->push(std::make_shared<EventsAlias::terrain_collision>(EventType::TERRAIN_COLLISION,entity,2));
        }else if(! isGround(topLeft(gbHeight, bounds)) && 
                 ! isGround(middleLeft(gbHeight, bounds)) && 
                   isGround(bottomLeft(gbHeight, bounds))){ 
            entity->addState(States::GROUND);
            entity->removeState(States::FALLING);
            // send event to detect we are in a left corner
            eventQueue->push(std::make_shared<EventsAlias::terrain_collision>(EventType::TERRAIN_COLLISION,entity,3));
        }else if(! isGround(topRight(gbHeight, bounds)) && 
                 ! isGround(middleRight(gbHeight, bounds)) && 
                   isGround(bottomRight(gbHeight, bounds))){
            entity->addState(States::GROUND);
            entity->removeState(States::FALLING);
            // send event to detect we are in a right corner
            eventQueue->push(std::make_shared<EventsAlias::terrain_collision>(EventType::TERRAIN_COLLISION,entity,4));
        }else{ // the entity is falling
            entity->removeState(States::GROUND);
            entity->addState(States::FALLING);
        }
    }
}
