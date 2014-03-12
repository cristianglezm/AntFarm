#include <World/World.hpp>

namespace ant{
    World::World(){
        entityManager.reset(new EntityManager());
        systemManager.reset(new SystemManager());
        eventQueue.reset(new EventQueue());
    }
    World::World(std::shared_ptr<EntityManager> entityManager,std::unique_ptr<SystemManager> systemManager,std::shared_ptr<EventQueue> eventQueue){
        this->entityManager = entityManager;
        this->eventQueue = eventQueue;
        this->systemManager = std::move(systemManager);
    }
    void World::setEntityManager(std::shared_ptr<EntityManager> entityManager){
        this->entityManager = entityManager;
        this->systemManager->setEntityManager(entityManager);
    }
    void World::setSystemManager(std::unique_ptr<SystemManager> systemManager){
        this->systemManager = std::move(systemManager);
        this->systemManager->setEntityManager(entityManager);
    }
    void World::setEventQueue(std::shared_ptr<EventQueue> eventQueue){
        this->eventQueue = eventQueue;
    }
    void World::setGameEventDispatcher(std::shared_ptr<GameEventDispatcher> ged){
        this->gameEventDispatcher = ged;
    }
    void World::update(sf::Time dt){
        this->systemManager->update(dt);
    }
    void World::render(){
        this->systemManager->render();
    }
    World::~World(){

    }
}
