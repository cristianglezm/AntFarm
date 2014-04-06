#include <SystemFactory/SystemFactory.hpp>

namespace ant{
    SystemFactory::SystemFactory()
    : gameEventDispatcher(new GameEventDispatcher())
    , eventQueue(new EventQueue()){}
    SystemFactory::SystemFactory(std::shared_ptr<GameEventDispatcher> ged,std::shared_ptr<EventQueue> eq)
    : gameEventDispatcher(ged)
    , eventQueue(eq){}
    void SystemFactory::setEventQueue(std::shared_ptr<EventQueue> eq){
        this->eventQueue = eq;
    }
    void SystemFactory::setGameEventDispatcher(std::shared_ptr<GameEventDispatcher> ged){
        this->gameEventDispatcher = ged;
    }
    std::shared_ptr<renderSystem> SystemFactory::createRenderSystem(){
        return std::shared_ptr<renderSystem>(new renderSystem());
    }
    std::shared_ptr<inputSystem> SystemFactory::createInputSystem(){
        /// TODO implement
        //return std::shared_ptr<inputSystem>(new inputSystem());
    }
    std::shared_ptr<collisionSystem> SystemFactory::createCollisionSystem(sf::FloatRect bounds){
        return std::shared_ptr<collisionSystem>(new collisionSystem(bounds));
    }
    std::shared_ptr<movementSystem> SystemFactory::createMovementSystem(){
        std::shared_ptr<movementSystem> m(new movementSystem());
        this->gameEventDispatcher->OnCollision().addObserver(m);
        return m;
;    }

    SystemFactory::~SystemFactory(){

    }
}
