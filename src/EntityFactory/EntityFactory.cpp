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
        std::unique_ptr<Entity> e(new Entity());
        ComponentSettings cs;
        /// @todo Limpiar y encontrar mejor forma de cargar variables para los componentes por defecto.
        if((mask & Ant) == Ant){
            cs.loadSettings("data/config/entities/Ant.json");
        }
        if((mask & Door) == Door){
                /// @todo change for door conf
            cs.loadSettings("data/config/entities/Ant.json");
        }
        if((mask & level) == level){
            /// @todo change for level conf
            cs.loadSettings("data/config/entities/Ant.json");
        }
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
        return std::move(e);
    }
    std::unique_ptr<Entity> EntityFactory::createEntity(long int mask, ComponentSettings& cs){
        std::unique_ptr<Entity> e(new Entity());
        /// @todo change
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
        return std::move(e);
    }
    void EntityFactory::setComponentFactory(std::shared_ptr<ComponentFactory> cf){
        this->componentFactory = cf;
    }
    EntityFactory::~EntityFactory(){

    }

}
