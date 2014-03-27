#include <EntityFactory/EntityFactory.hpp>

namespace ant{
    EntityFactory::EntityFactory(){
        componentFactory.reset(new ComponentFactory());
    }
    EntityFactory::EntityFactory(std::string json_filename){

    }
    void EntityFactory::createEntity(long int mask){
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
    }
    void EntityFactory::createEntity(long int mask, ComponentSettings& cs){

    }
    void EntityFactory::setComponentFactory(std::shared_ptr<ComponentFactory> cf){
        componentFactory = cf;
    }
    EntityFactory::~EntityFactory(){

    }

}
