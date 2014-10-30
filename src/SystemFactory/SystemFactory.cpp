#include <SystemFactory/SystemFactory.hpp>

namespace ant{
    SystemFactory::SystemFactory()
    : gameEventDispatcher(std::make_shared<GameEventDispatcher>())
    , eventQueue(std::make_shared<EventQueue>()){}
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
        auto s = std::make_shared<renderSystem>();
        s->setEventQueue(eventQueue);
        return s;
    }
    std::shared_ptr<collisionSystem> SystemFactory::createCollisionSystem(sf::FloatRect bounds,sf::VertexArray * GameMap){
        auto cs = std::make_shared<collisionSystem>(bounds,GameMap);
        cs->setEventQueue(eventQueue);
        return cs;
    }
    std::shared_ptr<movementSystem> SystemFactory::createMovementSystem(){
        auto m = std::make_shared<movementSystem>();
        gameEventDispatcher->onCollision.addObserver(m.get());
        m->setEventQueue(eventQueue);
        return m;
    }
    std::shared_ptr<gravitySystem> SystemFactory::createGravitySystem(float gravity){
        auto g = std::make_shared<gravitySystem>(gravity);
        g->setEventQueue(eventQueue);
        return g;
    }
    std::shared_ptr<spawnSystem> SystemFactory::createSpawnSystem(int nEntities,EntityFactory* ef,sf::Time ot,sf::Vector2f spawnPoint,long int state){
        auto sp = std::make_shared<spawnSystem>(nEntities,ef,ot,spawnPoint,state);
        gameEventDispatcher->spawnEvents.addObserver(sp.get());
        sp->setEventQueue(eventQueue);
        return sp;
    }
    std::shared_ptr<constructorSystem> SystemFactory::createConstructorSystem(sf::VertexArray* GameMap,sf::FloatRect bounds){
        auto csys = std::make_shared<constructorSystem>(GameMap,bounds);
        gameEventDispatcher->ClickEvents.addObserver(csys.get());
        gameEventDispatcher->ChangeCommand.addObserver(csys.get());
        gameEventDispatcher->onCollision.addObserver(csys.get());
        csys->setEventQueue(eventQueue);
        return csys;
    }
    std::shared_ptr<outSystem> SystemFactory::createOutSystem(int totalEntities){
        auto o = std::make_shared<outSystem>(totalEntities);
        gameEventDispatcher->outMap.addObserver(o.get());
        gameEventDispatcher->onCollision.addObserver(o.get());
        o->setEventQueue(eventQueue);
        return o;
    }
}
