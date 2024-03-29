#include <EntityFactory.hpp>

namespace ant{
    const ComponentsMask::Mask EntityFactory::Ant = ComponentsMask::COMPONENT_VELOCITY
                    | ComponentsMask::COMPONENT_SPRITE
                    | ComponentsMask::COMPONENT_TRANSFORM
                    | ComponentsMask::COMPONENT_COUNT
                    | ComponentsMask::COMPONENT_BOUNDS;
    const ComponentsMask::Mask EntityFactory::Door = ComponentsMask::COMPONENT_PASSAGE
                    | ComponentsMask::COMPONENT_TRANSFORM
                    | ComponentsMask::COMPONENT_SPRITE
                    | ComponentsMask::COMPONENT_BOUNDS;
    const ComponentsMask::Mask EntityFactory::InDoor = ComponentsMask::COMPONENT_TRANSFORM
                    | ComponentsMask::COMPONENT_SPRITE
                    | ComponentsMask::COMPONENT_IN;
    const ComponentsMask::Mask EntityFactory::OutDoor = ComponentsMask::COMPONENT_TRANSFORM
                    | ComponentsMask::COMPONENT_BOUNDS
                    | ComponentsMask::COMPONENT_SPRITE
                    | ComponentsMask::COMPONENT_OUT;
    const ComponentsMask::Mask EntityFactory::level = ComponentsMask::COMPONENT_DESTRUCTABLE
                    | ComponentsMask::COMPONENT_TRANSFORM
                    | ComponentsMask::COMPONENT_SPRITE;
    EntityFactory::EntityFactory()
    : componentFactory(std::make_shared<ComponentFactory>()){}
    EntityFactory::EntityFactory(const std::string& json)
    : componentFactory(std::make_shared<ComponentFactory>()){
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
    std::unique_ptr<Entity> EntityFactory::createEntity(ComponentsMask::Mask mask){
        ComponentSettings cs;
        if((mask & Ant) == Ant){
            cs.loadSettings(Config::ANT_FILE);
        }
        if((mask & InDoor) == InDoor){
            cs.loadSettings(Config::INDOOR_FILE);
        }
        if((mask & OutDoor) == OutDoor){
            cs.loadSettings(Config::OUTDOOR_FILE);
        }
        if((mask & level) == level){
            cs.loadSettings(Config::LEVEL_FILE);
        }
        return createEntity(mask,cs);
    }
    std::unique_ptr<Entity> EntityFactory::createEntity(ComponentsMask::Mask mask, ComponentSettings& cs){
        auto e = std::make_unique<Entity>();
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
        return e;
    }
    void EntityFactory::setComponentFactory(std::shared_ptr<ComponentFactory> cf){
        this->componentFactory = cf;
    }
}
