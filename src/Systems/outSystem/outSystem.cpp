#include <Systems/outSystem/outSystem.hpp>

namespace ant{
    outSystem::outSystem(){
        savedEntities = 0;
        totalEntities = 50;
    }
    outSystem::outSystem(int TotalEntities){
        totalEntities = TotalEntities;
        savedEntities = 0;
    }
    void outSystem::onNotify(std::shared_ptr<baseEvent> e){
        switch(e->getType()){
            case EventType::OUT_MAP:{
                auto& entity = std::get<0>(e->getAttributes<Entity*>());
                //entity->clear();
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
    void outSystem::update(sf::Time dt){
        EntityManager::iterator i = em->begin();
        while(i != em->end()){
            if((*i)->is(States::UNSAVED)){
               i = em->removeEntity(i);
               --totalEntities;
            }else if((*i)->is(States::SAVED)){
                ++savedEntities;
                i = em->removeEntity(i);
            }
            ++i;
        }
        if(totalEntities>0){
            if(savedEntities==totalEntities){
                eventQueue->push(std::shared_ptr<baseEvent>(new Event<>(EventType::LEVEL_COMPLETE)));
            }
        }else{
            eventQueue->push(std::shared_ptr<baseEvent>(new Event<>(EventType::LEVEL_FAILED)));
        }
    }
    outSystem::~outSystem(){

    }
}
