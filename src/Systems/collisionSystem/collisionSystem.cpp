#include <Systems/collisionSystem/collisionSystem.hpp>
#include <Event/EventsAlias.hpp>

namespace ant{
    collisionSystem::collisionSystem(sf::FloatRect bounds,sf::VertexArray* GameMap)
    : qtree(bounds)
    , gameBounds(bounds)
    , gameMap(GameMap){
        name = "collisionSystem";
        RequiredComponents = ComponentsMask::COMPONENT_TRANSFORM | ComponentsMask::COMPONENT_BOUNDS;
    }
    void collisionSystem::update(const sf::Time& dt){
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
         * Comprobamos si colisiona con los seis puntos
         * 1 esquina superior izquierda -> envia evento de colision con pared 0
         * 2 esquina superior derecha -> envia evento de colision con pared 1
         * 3 esquina inferior mediana izquierda -> envia evento de colision con escalon para subirlo 2
         * 4 esquina inferior izquierda -> Cambia estado de FALLING a GROUND
         * 5 esquina inferior mediana derecha -> envia evento de colision con escalon para subirlo 2
         * 6 esquina inferior derecha -> Cambia estado de FALLING a GROUND
         */
        int gbHeight = (int) gameBounds.height;
        auto& gm = *gameMap;
        static const auto ground = 255;
        if(gm[gbHeight * ((int)eBounds.left) + ((int)eBounds.top)].color.a == ground){
            eventQueue->push(std::make_shared<EventsAlias::terrain_collision>(EventType::TERRAIN_COLLISION,entity,0));
        }else if(gm[gbHeight * ((int)(eBounds.left+eBounds.width)) + ((int)eBounds.top)].color.a == ground){
            eventQueue->push(std::make_shared<EventsAlias::terrain_collision>(EventType::TERRAIN_COLLISION,entity,1));
        }else if(gm[gbHeight * ((int)(eBounds.left)) + ((int)(eBounds.top+eBounds.height/2))].color.a == ground){
            eventQueue->push(std::make_shared<EventsAlias::terrain_collision>(EventType::TERRAIN_COLLISION,entity,2));
            // subir escaleras
        }else if(gm[gbHeight * ((int)eBounds.left) + ((int)(eBounds.top+eBounds.height))].color.a == ground){
            entity->addState(States::GROUND);
            entity->removeState(States::FALLING);
            // enviamos evento para detectar que esta en una esquina
            eventQueue->push(std::make_shared<EventsAlias::terrain_collision>(EventType::TERRAIN_COLLISION,entity,3));
        }else if(gm[gbHeight * ((int)(eBounds.left+eBounds.width)) + ((int)(eBounds.top+(eBounds.height/2)))].color.a == ground){
            eventQueue->push(std::make_shared<EventsAlias::terrain_collision>(EventType::TERRAIN_COLLISION,entity,2));
            // subir escaleras
        }else if(gm[gbHeight * ((int)(eBounds.left+eBounds.width)) + ((int)(eBounds.top+eBounds.height))].color.a == ground){
            entity->addState(States::GROUND);
            entity->removeState(States::FALLING);
            // enviamos evento para detectar que esta en una esquina
            eventQueue->push(std::make_shared<EventsAlias::terrain_collision>(EventType::TERRAIN_COLLISION,entity,4));
        }else{
            entity->removeState(States::GROUND);
            entity->addState(States::FALLING);
        }
    }
}