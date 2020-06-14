#include <Systems/outSystem/outSystem.hpp>
#include <Event/EventsAlias.hpp>

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
                auto& entity = std::get<0>(e->getAttributes<EventsAlias::out_map>());
                entity->addState(States::UNSAVED);
            }
            break;
            case EventType::COLLISION_EVENT:{
                auto& entity1 = std::get<0>(e->getAttributes<EventsAlias::collision>());
                auto& entity2 = std::get<1>(e->getAttributes<EventsAlias::collision>());
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
        auto& entities = em->getEntities();
        auto removed = std::remove_if(std::begin(entities), std::end(entities),
                                        [this](std::unique_ptr<Entity>& e){
                                           if(e->is(States::UNSAVED)){
                                                --totalEntities;
                                                return true;
                                            }else if(e->is(States::SAVED)){
                                                ++savedEntities;
                                                eventQueue->push(std::make_shared<EventsAlias::update_score>(EventType::UPDATE_SCORE,1));
                                                return true;
                                            }
                                            return false;
                                        });
        if(removed != std::end(entities)){
            entities.erase(removed,std::end(entities));
        }
        if(totalEntities>0){
            if(savedEntities==totalEntities){
                eventQueue->push(std::make_shared<EventsAlias::level_complete>(EventType::LEVEL_COMPLETE));
            }
        }else{
            eventQueue->push(std::make_shared<EventsAlias::level_failed>(EventType::LEVEL_FAILED));
        }
    }
}