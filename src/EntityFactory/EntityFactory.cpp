#include <EntityFactory/EntityFactory.hpp>

namespace ant{
    EntityFactory::EntityFactory(){
        componentFactory.reset(new ComponentFactory());
    }
    EntityFactory::EntityFactory(const std::string& json){
        componentFactory.reset(new ComponentFactory());
        componentFactory->loadAssets(json);
    }
    bool EntityFactory::loadAssets(const std::string& json){
        return componentFactory->loadAssets(json);
    }
    bool EntityFactory::unloadAssets(){
        return componentFactory->unloadAssets();
    }
    void EntityFactory::setAssetManager(std::shared_ptr<AssetManager> assets){
        componentFactory->setAssetManager(assets);
    }
    std::unique_ptr<Entity> EntityFactory::createEntity(long int mask){
        ComponentSettings cs;
        /// @todo Limpiar y encontrar mejor forma de cargar variables para los componentes por defecto.
        if((mask & Ant) == Ant){
            cs.loadSettings("data/config/entities/Ant.json");
        }
        if((mask & InDoor) == InDoor){
                /// @todo change for door conf
            cs.loadSettings("data/config/entities/InDoor.json");
        }
        if((mask & OutDoor) == OutDoor){
                /// @todo change for door conf
            cs.loadSettings("data/config/entities/OutDoor.json");
        }
        if((mask & level) == level){
            /// @todo change for level conf
            cs.loadSettings("data/config/entities/Level.json");
        }
        return createEntity(mask,cs);
    }
    std::unique_ptr<Entity> EntityFactory::createEntity(long int mask, ComponentSettings& cs){
        std::unique_ptr<Entity> e(new Entity());
        e->setName(cs.entityName);
        if((mask & ComponentsMask::COMPONENT_TRANSFORM) == ComponentsMask::COMPONENT_TRANSFORM){
            e->addComponent(componentFactory->createTransform(cs.position,cs.scale,cs.rotation));
        }
        if((mask & ComponentsMask::COMPONENT_VELOCITY) == ComponentsMask::COMPONENT_VELOCITY){
            e->addComponent(componentFactory->createVelocity(cs.getSpeed(),cs.minSpeed,cs.maxSpeed));
        }
        if((mask & ComponentsMask::COMPONENT_BOUNDS) == ComponentsMask::COMPONENT_BOUNDS){
            e->addComponent(componentFactory->createBounds(cs.bounds));
        }
        if((mask & ComponentsMask::COMPONENT_SPRITE) == ComponentsMask::COMPONENT_SPRITE){
            e->addComponent(componentFactory->createSprite(cs.spriteID));
        }
        if((mask & ComponentsMask::COMPONENT_DESTRUCTABLE) == ComponentsMask::COMPONENT_DESTRUCTABLE){
            e->addComponent(componentFactory->createDestructable(cs.DestructiblePosition,cs.imageID));
        }
        if((mask & ComponentsMask::COMPONENT_OUT) == ComponentsMask::COMPONENT_OUT){
            e->addComponent(componentFactory->createOut());
        }
        if((mask & ComponentsMask::COMPONENT_IN) == ComponentsMask::COMPONENT_IN){
            e->addComponent(componentFactory->createIn());
        }
        if((mask & ComponentsMask::COMPONENT_COUNT) == ComponentsMask::COMPONENT_COUNT){
            e->addComponent(componentFactory->createCounter(cs.count));
        }
        return std::move(e);
    }
    void EntityFactory::setComponentFactory(std::shared_ptr<ComponentFactory> cf){
        this->componentFactory = cf;
    }
    EntityFactory::~EntityFactory(){

    }

}
