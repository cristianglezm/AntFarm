#include <WorldFactory/WorldFactory.hpp>

namespace ant{
    WorldFactory::WorldFactory(): nestId(0),battlefieldId(0){
        gameEventDispatcher.reset(new GameEventDispatcher());
        eventQueue.reset(new EventQueue());
        entityFactory.reset(new EntityFactory());
        systemFactory.reset(new SystemFactory(gameEventDispatcher,eventQueue));
    }
    WorldFactory::WorldFactory(std::shared_ptr<GameEventDispatcher> ged,std::shared_ptr<EventQueue> eq){
        nestId = 0;
        battlefieldId = 0;
        entityFactory.reset(new EntityFactory());
        gameEventDispatcher = ged;
        eventQueue = eq;
        systemFactory.reset(new SystemFactory(gameEventDispatcher,eventQueue));
    }
    bool WorldFactory::loadAssets(const std::string& json){
        return entityFactory->loadAssets(json);
    }
    bool WorldFactory::unloadAssets(){
        return entityFactory->unloadAssets();
    }
    void WorldFactory::setAssetManager(std::shared_ptr<AssetManager> assets){
        entityFactory->setAssetManager(assets);
    }
    std::unique_ptr<World> WorldFactory::createNest(sf::FloatRect bounds){
        std::unique_ptr<World> w(new World(nestId));
        auto em = w->getEntityManager();
        std::unique_ptr<SystemManager> sm(new SystemManager());
        sm->addSystem(systemFactory->createMovementSystem());
        sm->addSystem(systemFactory->createCollisionSystem(bounds));
        sm->addSystem(systemFactory->createRenderSystem());
        em->addEntity(entityFactory->createEntity(EntityFactory::Nest));
        em->addEntity(entityFactory->createEntity(EntityFactory::AntQueen));
        w->setEventQueue(eventQueue);
        w->setEntityManager(em);
        w->setSystemManager(std::move(sm));
        ++nestId;
        return std::move(w);
    }
    std::unique_ptr<World> WorldFactory::createBattlefield(sf::FloatRect bounds){
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
