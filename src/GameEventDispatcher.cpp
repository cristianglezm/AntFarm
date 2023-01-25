#include <GameEventDispatcher.hpp>

namespace ant{
    bool GameEventDispatcher::DispatchEvent(std::shared_ptr<baseEvent> e){
        switch(e->getType()){
            case EventType::TERRAIN_COLLISION:
            case EventType::COLLISION_EVENT:
                onCollision.notifyObservers(e);
                return true;
            case EventType::CHANGE_OVERTIME:
            case EventType::CHANGE_NENTITIES:
                spawnEvents.notifyObservers(e);
                return true;
            case EventType::CHANGE_COMMAND:
                ChangeCommand.notifyObservers(e);
                return true;
            case EventType::SELECT_ENTITY:
                ClickEvents.notifyObservers(e);
                return true;
            case EventType::OUT_MAP:
                outMap.notifyObservers(e);
                return true;
            case EventType::LEVEL_COMPLETE:
                LevelComplete.notifyObservers(e);
                return true;
            case EventType::LEVEL_FAILED:
                LevelFailed.notifyObservers(e);
                return true;
            case EventType::UPDATE_SCORE:
                UpdateScore.notifyObservers(e);
                return true;
        }
        return false;
    }
}
