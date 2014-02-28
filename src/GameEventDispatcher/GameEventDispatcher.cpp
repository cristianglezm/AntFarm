#include <GameEventDispatcher/GameEventDispatcher.hpp>
namespace ant{
    GameEventDispatcher::GameEventDispatcher(){

    }
    bool GameEventDispatcher::DispatchEvent(Event e){
        switch(e.getType()){
            case 0:
                onCollision.notifyObservers(e);
                break;
        }
    }
    GameEventDispatcher::~GameEventDispatcher(){

    }
};
