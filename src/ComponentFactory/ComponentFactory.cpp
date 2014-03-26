#include <ComponentFactory/ComponentFactory.hpp>

namespace ant{
            ComponentFactory::ComponentFactory(std::shared_ptr<AssetManager> assets){
                this->assets = assets;
            }
            void ComponentFactory::setAssetManager(std::shared_ptr<AssetManager> assets){
                this->assets = assets;
            }
            std::unique_ptr<baseComponent> ComponentFactory::createTransform(sf::Vector2f position,sf::Vector2f scale,float rotation){
                std::unique_ptr<baseComponent> c(new Component<sf::Vector2f,sf::Vector2f,float>(ComponentsMask::COMPONENT_TRANSFORM,
                                                                                              position,scale,rotation));
                return std::move(c);
            }
            std::unique_ptr<baseComponent> ComponentFactory::createBounds(sf::FloatRect bounds){
                std::unique_ptr<baseComponent> c(new Component<sf::FloatRect>(ComponentsMask::COMPONENT_BOUNDS,bounds));
                return std::move(c);
            }
            std::unique_ptr<baseComponent> ComponentFactory::createSprite(std::string id){
                std::unique_ptr<baseComponent> c(new Component<std::unique_ptr<sf::Sprite>>(ComponentsMask::COMPONENT_SPRITE,std::unique_ptr<sf::Sprite>(new sf::Sprite((assets->getTexture(id))))));
                return std::move(c);
            }
            ComponentFactory::~ComponentFactory(){

            }

}
