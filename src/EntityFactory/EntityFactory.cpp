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
        switch(mask){
            case Ant:

                break;
            case AntQueen:

                break;
        }
        if((mask & ComponentsMask::COMPONENT_BOUNDS) == ComponentsMask::COMPONENT_BOUNDS){
            e->addComponent(componentFactory->createBounds(sf::FloatRect(0,0,0,0)));
        }
        if((mask & ComponentsMask::COMPONENT_SPRITE) == ComponentsMask::COMPONENT_SPRITE){

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
