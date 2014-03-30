#include <ComponentFactory/ComponentFactory.hpp>

namespace ant{
            std::unique_ptr<sf::VertexArray> ComponentFactory::mapImage(const sf::Vector2f& position,sf::Image& img){
                int xWidth = img.getSize().x;
                int yHeight = img.getSize().y;
                std::unique_ptr<sf::VertexArray> destructible(new sf::VertexArray(sf::Points,xWidth*yHeight));
                for(int x=0;x<xWidth;++x){
                    for(int y=0;y<yHeight;++y){
                        (*destructible)[xWidth*x+y].color = img.getPixel(x,y);
                    }
                }
                xWidth += position.x;
                yHeight += position.y;
                for(int x=position.x;x<xWidth;++x){
                    for(int y=position.y;y<yHeight;++y){
                        (*destructible)[xWidth*x+y].position = sf::Vector2f(x,y);
                    }
                }
                return std::move(destructible);
            }
            ComponentFactory::ComponentFactory(){
                assets.reset(new AssetManager());
            }
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
            std::unique_ptr<baseComponent> ComponentFactory::createDestructable(sf::Vector2f position,const std::string& imageID){
                std::unique_ptr<sf::VertexArray> destructable = mapImage(position,assets->getImage(imageID));
                std::unique_ptr<baseComponent> c(new Component<std::unique_ptr<sf::VertexArray>>(ComponentsMask::COMPONENT_DESTRUCTABLE,std::move(destructable)));
            }
            std::unique_ptr<baseComponent> ComponentFactory::createSprite(std::string id){
                std::unique_ptr<baseComponent> c(new Component<std::unique_ptr<sf::Sprite>>(ComponentsMask::COMPONENT_SPRITE,std::unique_ptr<sf::Sprite>(new sf::Sprite((assets->getTexture(id))))));
                return std::move(c);
            }
            ComponentFactory::~ComponentFactory(){

            }

}
