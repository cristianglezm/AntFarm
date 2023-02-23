#include <WorldFactory.hpp>
#include <Components/ComponentsAlias.hpp>

namespace ant{
    WorldFactory::WorldFactory()
    : entityFactory(std::make_shared<EntityFactory>())
    , eventQueue(std::make_shared<EventQueue>())
    , gameEventDispatcher(std::make_shared<GameEventDispatcher>())
    , systemFactory(std::make_shared<SystemFactory>(gameEventDispatcher,eventQueue))
    , lvlID(0){}
    WorldFactory::WorldFactory(std::shared_ptr<GameEventDispatcher> ged,std::shared_ptr<EventQueue> eq)
    : entityFactory(std::make_shared<EntityFactory>())
    , eventQueue(eq)
    , gameEventDispatcher(ged)
    , systemFactory(std::make_shared<SystemFactory>(gameEventDispatcher,eventQueue))
    , lvlID(0){}
    bool WorldFactory::loadAssets(const std::string& json){
        return entityFactory->loadAssets(json);
    }
    bool WorldFactory::unloadAssets(){
        return entityFactory->unloadAssets();
    }
    void WorldFactory::setAssetManager(std::shared_ptr<AssetManager> assets){
        entityFactory->setAssetManager(assets);
    }
    std::unique_ptr<World> WorldFactory::create(const std::string& name,const std::string& background,const sf::Image& lvl,int nEntities,sf::Time overTime,sf::FloatRect bounds){
        std::unique_ptr<World> w(std::make_unique<World>(lvlID));
        auto em = w->getEntityManager();
        auto assets = getAssetManager();
        std::unique_ptr<SystemManager> sm(std::make_unique<SystemManager>());
        std::unique_ptr<sf::Image> img(std::make_unique<sf::Image>());

        img->create(bounds.width,bounds.height,sf::Color::Transparent);
        int width = lvl.getSize().x;
        int height = lvl.getSize().y;
        bool hasEnteredInDoor = false;
        bool hasEnteredOutDoor = false;
        sf::Vector2f inDoor;
        sf::Vector2f outDoor;
        sf::Color Brown(128,64,0,255);
        sf::Color lightBrown(150,75,0,255);
        std::mt19937 engine(std::random_device{}());
        std::bernoulli_distribution dice(0.5);
        double xScale = bounds.width / width;
        double yScale = bounds.height / height;
        for(int x=0;x<width;++x){
            for(int y=0;y<height;++y){
                sf::Color color = lvl.getPixel(x,y);
                if(color == sf::Color::Black){
                    for(int i=0;i<xScale;++i){
                        for(int j=0;j<yScale;++j){
                            img->setPixel(x * xScale + i, y * yScale + j, dice(engine) ? Brown:lightBrown);
                            img->setPixel(x * xScale, y * yScale+j, dice(engine) ? Brown:lightBrown);
                            img->setPixel(x * xScale + i, y * yScale, dice(engine) ? Brown:lightBrown);
                        }
                    }
                    img->setPixel(x*xScale,y*yScale,lightBrown);
                }else if(color == sf::Color::Red){
                    hasEnteredInDoor = true;
                    inDoor = sf::Vector2f(x * xScale, y * yScale);
                }else if(color == sf::Color::Green){
                    hasEnteredOutDoor = true;
                    outDoor = sf::Vector2f(x * xScale,y * yScale);
                }
            }
        }
        ComponentSettings cs;
        cs.loadSettings(Config::LEVEL_FILE);
        cs.imageID = name;
        cs.spriteID = background;
        cs.entityName = name;
        assets->addImage(name,std::move(img));
        auto e = entityFactory->createEntity(EntityFactory::level,cs);
        auto& sprite = e->getComponent(ComponentsMask::COMPONENT_SPRITE)
                             ->getProperties<ComponentsAlias::sprite>();
        auto& transform = e->getComponent(ComponentsMask::COMPONENT_TRANSFORM)
                                ->getProperties<ComponentsAlias::transform>();
        auto& spr = std::get<1>(sprite);
        auto boundsSpr =  spr->getLocalBounds();
        sf::Vector2f& scale = std::get<1>(transform);
        scale.x = bounds.width / boundsSpr.width;
        scale.y = bounds.height / boundsSpr.height;
        em->addEntity(std::move(e));
	// systems need to keep this order or events from deleted entities will seg fault commit [310f46e14]
        sm->addSystem(systemFactory->createOutSystem(nEntities));
        sm->addSystem(systemFactory->createRenderSystem());
        auto& properties = em->getEntity(name)->getComponent(ComponentsMask::COMPONENT_DESTRUCTABLE)
                                        ->getProperties<ComponentsAlias::destructable>();
        auto& destructable = std::get<1>(properties);
        sm->addSystem(systemFactory->createConstructorSystem(destructable.get(),bounds));
        sm->addSystem(systemFactory->createCollisionSystem(bounds,destructable.get()));
        sm->addSystem(systemFactory->createGravitySystem(1.9));
        sm->addSystem(systemFactory->createMovementSystem());
        if(hasEnteredInDoor){
            ComponentSettings cs;
            cs.loadSettings(Config::INDOOR_FILE);
            cs.position = inDoor;
            em->addEntity(entityFactory->createEntity(EntityFactory::InDoor,cs));
            sm->addSystem(systemFactory->createSpawnSystem(nEntities,entityFactory.get(),overTime,{inDoor.x * 1.25f, inDoor.y * 1.25f},States::FALLING));
        }
        if(hasEnteredOutDoor){
            ComponentSettings cs;
            cs.loadSettings(Config::OUTDOOR_FILE);
            cs.bounds.width = cs.bounds.width*cs.scale.x;
            cs.bounds.height = cs.bounds.height*cs.scale.y;
            cs.position = outDoor - sf::Vector2f(cs.bounds.width,cs.bounds.height-10);
            em->addEntity(entityFactory->createEntity(EntityFactory::OutDoor,cs));
        }
        w->setEventQueue(eventQueue);
        w->setEntityManager(em);
        w->setSystemManager(std::move(sm));
        ++lvlID;
        return w;
    }
    void WorldFactory::setEntityFactory(std::shared_ptr<EntityFactory> ef){
        entityFactory = ef;
    }
    void WorldFactory::setEventQueue(std::shared_ptr<EventQueue> eq){
        eventQueue = eq;
        systemFactory->setEventQueue(eventQueue);
    }
    void WorldFactory::setGameEventDispatcher(std::shared_ptr<GameEventDispatcher> ged){
        gameEventDispatcher = ged;
        systemFactory->setGameEventDispatcher(ged);
    }
}
