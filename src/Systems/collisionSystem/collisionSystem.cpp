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
                //auto& rotation = std::get<2>(cTransf);
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
                    if(entity1.get() != entity2){
                        auto& properties2 = entity2->getComponent(ComponentsMask::COMPONENT_BOUNDS)
                                            ->getProperties<sf::FloatRect>();
                        auto& eBounds2 = std::get<0>(properties2);
                        if(eBounds1.intersects(eBounds2)){
                            eventQueue->push(std::shared_ptr<baseEvent>(new Event<Entity*,Entity*>(
                                                EventType::COLLISION_EVENT,entity1.get(),entity2)));
                        }
                        if(eBounds2.intersects(eBounds1)){
                            eventQueue->push(std::shared_ptr<baseEvent>(new Event<Entity*,Entity*>(
                                                EventType::COLLISION_EVENT,entity1.get(),entity2)));
                        }
                        if(!Utils::RectContains(eBounds1,gameBounds)){
                            eventQueue->push(std::shared_ptr<baseEvent>(new Event<Entity*>(
                                                EventType::OUT_MAP,entity1.get())));
                        }else{
                            testTerrainCollision(entity1.get(),eBounds1);
                        }
                        if(!Utils::RectContains(eBounds2,gameBounds)){
                            eventQueue->push(std::shared_ptr<baseEvent>(new Event<Entity*>(
                                                EventType::OUT_MAP,entity2)));
                        }else{
                            testTerrainCollision(entity2,eBounds2);
                        }
                    }
                }
            }
        }
    }
    void collisionSystem::testTerrainCollision(Entity* entity,const sf::FloatRect& eBounds){
        /* Comprobamos si colisiona con los seis puntos
         * 1 esquina superior izquierda -> envia evento de colision con suelo 0
         * 2 esquina superior derecha -> envia evento de colision con suelo 1
         * 3 esquina inferior mediana izquierda -> envia evento de colision con suelo para subir escalones 2
         * 4 esquina inferior izquierda -> Cambia estado de FALLING a GROUND
         * 5 esquina inferior mediana derecha -> envia evento de colision con suelo para subir escalones 2
         * 6 esquina inferior derecha -> Cambia estado de FALLING a GROUND
         */
        if((*gameMap)[((int)gameBounds.height) * ((int)eBounds.left) + ((int)eBounds.top)].color.a == 255){
            eventQueue->push(std::shared_ptr<baseEvent>(new Event<Entity*,int>(
                                EventType::TERRAIN_COLLISION,entity,0)));
        }else if((*gameMap)[((int)gameBounds.height) * ((int)(eBounds.left+eBounds.width)) + ((int)eBounds.top)].color.a == 255){
            eventQueue->push(std::shared_ptr<baseEvent>(new Event<Entity*,int>(
                                EventType::TERRAIN_COLLISION,entity,1)));
        }else if((*gameMap)[((int)gameBounds.height) * ((int)(eBounds.left)) + ((int)(eBounds.top+eBounds.height/2))].color.a == 255){
            eventQueue->push(std::shared_ptr<baseEvent>(new Event<Entity*,int>(
                                EventType::TERRAIN_COLLISION,entity,2)));
                // subir escaleras
        }else if((*gameMap)[((int)gameBounds.height) * ((int)eBounds.left) + ((int)(eBounds.top+eBounds.height))].color.a == 255){
            entity->addState(States::GROUND);
            entity->removeState(States::FALLING);
            // enviamos evento para detectar que esta en una esquina
            eventQueue->push(std::shared_ptr<baseEvent>(new Event<Entity*,int>(
                                EventType::TERRAIN_COLLISION,entity,3)));
        }else if((*gameMap)[((int)gameBounds.height) * ((int)(eBounds.left+eBounds.width)) + ((int)(eBounds.top+(eBounds.height/2)))].color.a == 255){
                eventQueue->push(std::shared_ptr<baseEvent>(new Event<Entity*,int>(
                                EventType::TERRAIN_COLLISION,entity,2)));
                // subir escaleras
        }else if((*gameMap)[((int)gameBounds.height) * ((int)(eBounds.left+eBounds.width)) + ((int)(eBounds.top+eBounds.height))].color.a == 255){
                entity->addState(States::GROUND);
                entity->removeState(States::FALLING);
                // enviamos evento para detectar que esta en una esquina
                eventQueue->push(std::shared_ptr<baseEvent>(new Event<Entity*,int>(
                                EventType::TERRAIN_COLLISION,entity,4)));
        }else{
            entity->removeState(States::GROUND);
            entity->addState(States::FALLING);
        }
    }
    collisionSystem::~collisionSystem(){

    }
}
