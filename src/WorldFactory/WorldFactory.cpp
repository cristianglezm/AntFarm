#include <WorldFactory/WorldFactory.hpp>

namespace ant{
    WorldFactory::WorldFactory(): nestId(0),battlefieldId(0){
        gameEventDispatcher.reset(new GameEventDispatcher());
        eventQueue.reset(new EventQueue());
        entityFactory.reset(new EntityFactory());
    }
    WorldFactory::WorldFactory(std::shared_ptr<GameEventDispatcher> ged,std::shared_ptr<EventQueue> eq){
        nestId = 0;
        battlefieldId = 0;
        entityFactory.reset(new EntityFactory());
        gameEventDispatcher = ged;
        eventQueue = eq;
    }
    std::unique_ptr<World> WorldFactory::createNest(){
        std::unique_ptr<World> w(new World(nestId));
        auto em = w->getEntityManager();
        em->addEntity(entityFactory->createEntity(EntityFactory::Ant));
        ++nestId;
        return std::move(w);
    }
    std::unique_ptr<World> WorldFactory::createBattlefield(){
        std::unique_ptr<World> w(new World(battlefieldId));

        ++battlefieldId;
        return std::move(w);
    }
    void WorldFactory::setEntityFactory(std::shared_ptr<EntityFactory> ef){
        entityFactory = ef;
    }
    void WorldFactory::setEventQueue(std::shared_ptr<EventQueue> eq){
        eventQueue = eq;
    }
    void WorldFactory::setGameEventDispatcher(std::shared_ptr<GameEventDispatcher> ged){
        gameEventDispatcher = ged;
    }
    WorldFactory::~WorldFactory(){

    }
}
