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
        std::shared_ptr<renderSystem> s(new renderSystem());
        s->setEventQueue(eventQueue);
        return s;
    }
    std::shared_ptr<inputSystem> SystemFactory::createInputSystem(){
        /// @todo implement
        //return std::shared_ptr<inputSystem>(new inputSystem());
    }
    std::shared_ptr<collisionSystem> SystemFactory::createCollisionSystem(sf::FloatRect bounds){
        return std::shared_ptr<collisionSystem>(new collisionSystem(bounds));
    }
    std::shared_ptr<movementSystem> SystemFactory::createMovementSystem(){
        std::shared_ptr<movementSystem> m(new movementSystem());
        gameEventDispatcher->onCollision.addObserver(m);
        return m;
    }
    std::shared_ptr<spawnSystem> SystemFactory::createSpawnSystem(int nEntities,EntityFactory* ef,sf::Time ot){
        std::shared_ptr<spawnSystem> sp(new spawnSystem(nEntities,ef,ot));
        gameEventDispatcher->spawnEvents.addObserver(sp);
        return sp;
    }
    SystemFactory::~SystemFactory(){

    }
}
