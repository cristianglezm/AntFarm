#include <Systems/constructorSystem/constructorSystem.hpp>

namespace ant{
    constructorSystem::constructorSystem(sf::VertexArray* map,sf::FloatRect boundsMap){
        name = "constructionSystem";
        this->map = map;
        this->boundsMap = boundsMap;
        readyToBuild = false;
    }
    void constructorSystem::onNotify(std::shared_ptr<baseEvent> e){
        switch(e->getType()){
            case EventType::CHANGE_COMMAND:{
                build = std::get<0>(e->getAttributes<command>());
                readyToBuild = true;
            }
                break;
            case EventType::SELECT_ENTITY:{
                auto& clickedPoint = std::get<0>(e->getAttributes<sf::Vector2i>());
                for(auto& entity:em->getEntities()){
                    if(entity->hasComponent(ComponentsMask::COMPONENT_BOUNDS)){
                        auto& bounds = std::get<0>(entity->getComponent(ComponentsMask::COMPONENT_BOUNDS)
                                                            ->getProperties<sf::FloatRect>());
                        if(bounds.contains(clickedPoint.x,clickedPoint.y)){
                            entity->addState(States::BUILDING);
                            return;
                        }
                    }
                }
            }
                break;
        }
    }
    void constructorSystem::update(sf::Time dt){
        if(readyToBuild){
            for(auto& e: em->getEntities()){
                if(e->is(States::BUILDING) && e->hasComponent(ComponentsMask::COMPONENT_COUNT)){
                    auto& count = std::get<0>(e->getComponent(ComponentsMask::COMPONENT_COUNT)->getProperties<int>());
                    if(count <=0){
                        e->removeState(States::BUILDING);
                        count = 10;
                    }else{
                        --count;
                        (*build)(e.get(),map,boundsMap);
                    }
                }
            }
        }
    }
    void constructorSystem::render(sf::RenderWindow& win){
        return;
    }
    constructorSystem::~constructorSystem(){}
}
