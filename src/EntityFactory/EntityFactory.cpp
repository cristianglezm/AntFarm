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
        //ComponentSettings cs;
        /// @todo Limpiar y encontrar mejor forma de cargar variables para los componentes por defecto.
        std::string id = "Ant";
        if((mask & Ant) == Ant){
            id = "Ant";
        }
        if((mask & Door) == Door){
            id = "AntQueen";
        }
        if((mask & level) == level){
            id = "NestBackground";
        }
        if((mask & ComponentsMask::COMPONENT_TRANSFORM) == ComponentsMask::COMPONENT_TRANSFORM){
            e->addComponent(componentFactory->createTransform(sf::Vector2f(0,0),sf::Vector2f(1,1),0));
        }
        if((mask & ComponentsMask::COMPONENT_VELOCITY) == ComponentsMask::COMPONENT_VELOCITY){
            e->addComponent(componentFactory->createVelocity(0.1,0.0,1));
        }
        if((mask & ComponentsMask::COMPONENT_BOUNDS) == ComponentsMask::COMPONENT_BOUNDS){
            e->addComponent(componentFactory->createBounds(sf::FloatRect(0,0,1,1)));
        }
        if((mask & ComponentsMask::COMPONENT_SPRITE) == ComponentsMask::COMPONENT_SPRITE){
            e->addComponent(componentFactory->createSprite(id));
        }
        if((mask & ComponentsMask::COMPONENT_DESTRUCTABLE) == ComponentsMask::COMPONENT_DESTRUCTABLE){
                id= "NestDestructable";
            e->addComponent(componentFactory->createDestructable(sf::Vector2f(0,0),id));
        }
        return std::move(e);
    }
    std::unique_ptr<Entity> EntityFactory::createEntity(long int mask, ComponentSettings& cs){
        std::unique_ptr<Entity> e(new Entity());
        return std::move(e);
    }
    void EntityFactory::setComponentFactory(std::shared_ptr<ComponentFactory> cf){
        this->componentFactory = cf;
    }
    EntityFactory::~EntityFactory(){

    }

}
