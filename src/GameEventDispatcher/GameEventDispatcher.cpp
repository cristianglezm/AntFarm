#include <GameEventDispatcher/GameEventDispatcher.hpp>
namespace ant{
    GameEventDispatcher::GameEventDispatcher(){

    }
    bool GameEventDispatcher::DispatchEvent(std::shared_ptr<baseEvent> e){
        switch(e->getType()){
            case EventType::COLLISION_EVENT:
                onCollision.notifyObservers(e);
                return true;
                break;
        }
        return false;
    }
    GameEventDispatcher::~GameEventDispatcher(){

    }
}
