#include <Systems/outSystem/outSystem.hpp>

namespace ant{
    outSystem::outSystem()
    : totalEntities(50)
    , savedEntities(0){
        name = "outSystem";
    }
    outSystem::outSystem(const int& TotalEntities)
    : totalEntities(TotalEntities)
    , savedEntities(0){
        name = "outSystem";
    }
    void outSystem::onNotify(std::shared_ptr<baseEvent> e){
        switch(e->getType()){
            case EventType::OUT_MAP:{
                auto& entity = std::get<0>(e->getAttributes<Entity*>());
                entity->addState(States::UNSAVED);
            }
                break;
            case EventType::COLLISION_EVENT:{
                auto& entity1 = std::get<0>(e->getAttributes<Entity*,Entity*>());
                auto& entity2 = std::get<1>(e->getAttributes<Entity*,Entity*>());
                if(entity1->hasComponent(ComponentsMask::COMPONENT_OUT)
                   && !(entity2->hasComponent(ComponentsMask::COMPONENT_OUT))){
                    entity2->addState(States::SAVED);
                }else if(entity2->hasComponent(ComponentsMask::COMPONENT_OUT)
                         && !(entity1->hasComponent(ComponentsMask::COMPONENT_OUT))){
                    entity1->addState(States::SAVED);
                }
            }
                break;
        }
    }
    void outSystem::render(sf::RenderWindow& win){
        return;
    }
    void outSystem::update(const sf::Time& dt){
        EntityManager::iterator i = em->begin();
        while(i != em->end()){
            if((*i)->is(States::UNSAVED)){
                i = em->removeEntity(i);
                --totalEntities;
            }else if((*i)->is(States::SAVED)){
                i = em->removeEntity(i);
                ++savedEntities;
            }
            ++i;
        }
        if(totalEntities>0){
            if(savedEntities==totalEntities){
                eventQueue->push(std::make_shared<Event<>>(EventType::LEVEL_COMPLETE));
            }
        }else{
            eventQueue->push(std::make_shared<Event<>>(EventType::LEVEL_FAILED));
        }
    }
}
