#include <World/World.hpp>

namespace ant{
    World::World()
    : eventQueue(std::make_shared<EventQueue>())
    , entityManager(std::make_shared<EntityManager>())
    , systemManager(Utils::makeUniquePtr<SystemManager>()){}
    World::World(long int id)
    : id(id)
    , eventQueue(std::make_shared<EventQueue>())
    , entityManager(std::make_shared<EntityManager>())
    , systemManager(Utils::makeUniquePtr<SystemManager>()){}
    World::World(long int id,std::shared_ptr<EntityManager> eM,std::unique_ptr<SystemManager> sM,std::shared_ptr<EventQueue> eQ)
    : id(id)
    , eventQueue(eQ)
    , entityManager(eM)
    , systemManager(std::move(sM)){}
    void World::setEntityManager(std::shared_ptr<EntityManager> eM){
        entityManager = eM;
        systemManager->setEntityManager(entityManager);
    }
    void World::setSystemManager(std::unique_ptr<SystemManager> sM){
        systemManager = std::move(sM);
        systemManager->setEntityManager(entityManager);
        systemManager->setEventQueue(eventQueue);
    }
    void World::setEventQueue(std::shared_ptr<EventQueue> eQ){
        eventQueue = eQ;
    }
    void World::setGameEventDispatcher(std::shared_ptr<GameEventDispatcher> ged){
        gameEventDispatcher = ged;
    }
    void World::setId(long int id){
        this->id = id;
    }
    void World::update(const sf::Time& dt){
        systemManager->update(dt);
    }
    void World::render(sf::RenderWindow& win){
        systemManager->render(win);
    }
}
