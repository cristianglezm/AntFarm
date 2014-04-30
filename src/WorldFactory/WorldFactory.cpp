#include <WorldFactory/WorldFactory.hpp>

namespace ant{
    WorldFactory::WorldFactory(){
        gameEventDispatcher.reset(new GameEventDispatcher());
        eventQueue.reset(new EventQueue());
        entityFactory.reset(new EntityFactory());
        systemFactory.reset(new SystemFactory(gameEventDispatcher,eventQueue));
    }
    WorldFactory::WorldFactory(std::shared_ptr<GameEventDispatcher> ged,std::shared_ptr<EventQueue> eq){
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
    std::unique_ptr<World> WorldFactory::create(const sf::Image& lvl,int nEntities,sf::Time overTime,sf::FloatRect bounds){
        std::unique_ptr<World> w(new World(0));
        /// @todo refactorizar, leer imagen y crear level.
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
