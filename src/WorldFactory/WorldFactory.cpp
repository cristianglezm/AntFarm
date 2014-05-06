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
    std::unique_ptr<World> WorldFactory::create(const std::string& name,const sf::Image& lvl,int nEntities,sf::Time overTime,sf::FloatRect bounds){
        std::unique_ptr<World> w(new World(0));
        /// @todo refactorizar, leer imagen y crear level.
        /// comprueba si esta el nivel en assets si no esta crea imagen, limpia alpha procesa imagen lvl i crea el nivel
        auto em = w->getEntityManager();
        auto assets = getAssetManager();
        std::unique_ptr<SystemManager> sm(new SystemManager());
        if(!assets->hasImage(name)){
            std::unique_ptr<sf::Image> img(new sf::Image());
            img->create(bounds.width,bounds.height,sf::Color::Transparent);
            int width = lvl.getSize().x;
            int height = lvl.getSize().y;
            for(int x=0;x<width;++x){
                for(int y=0;y<height;++y){
                    sf::Color color = lvl.getPixel(x,y);
                        if(color == sf::Color::Black){
                                for(int i=0;i<10;++i){
                                        for(int j=0;j<10;++j){
                                            img->setPixel(x*10+i,y*10+j,sf::Color::Cyan);
                                            img->setPixel(x*10,y*10+j,sf::Color::Cyan);
                                            img->setPixel(x*10+i,y*10,sf::Color::Cyan);
                                        }
                                }
                                img->setPixel(x*10,y*10,sf::Color::Cyan);
                        }else if(color == sf::Color::Red){
                                ComponentSettings cs;
                                /// @todo Completar
                                cs.loadSettings("data/config/entities/Ant.json");
                                cs.position = sf::Vector2f((x*10),(y*10));
                                em->addEntity(entityFactory->createEntity(EntityFactory::Door));
                        }
                }
            }
            ComponentSettings cs;
            cs.loadSettings("data/config/entities/Ant.json");
            cs.imageID = name;
            img->saveToFile("tmp.png");
            assets->addImage(name,"tmp.png");
            em->addEntity(entityFactory->createEntity(ComponentsMask::COMPONENT_DESTRUCTABLE,cs));
        }
        sm->addSystem(systemFactory->createMovementSystem());
        sm->addSystem(systemFactory->createCollisionSystem(bounds));
        sm->addSystem(systemFactory->createRenderSystem());
        //em->addEntity(entityFactory->createEntity(EntityFactory::Nest));
        //em->addEntity(entityFactory->createEntity(EntityFactory::AntQueen));
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
