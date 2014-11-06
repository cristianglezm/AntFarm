#include <ComponentFactory/ComponentFactory.hpp>

namespace ant{
            std::unique_ptr<sf::VertexArray> ComponentFactory::mapImage(const sf::Vector2f& position,sf::Image& img,sf::FloatRect* bounds){
                int xWidth = img.getSize().x;
                int yHeight = img.getSize().y;
                bounds->height = yHeight;
                bounds->width = xWidth;
                bounds->left = position.x;
                bounds->top = position.y;
                std::unique_ptr<sf::VertexArray> destructible(new sf::VertexArray(sf::Points,xWidth*yHeight));
                for(int x=0;x<xWidth;++x){
                    for(int y=0;y<yHeight;++y){
                        (*destructible)[yHeight*x+y].color = img.getPixel(x,y);
                        (*destructible)[yHeight*x+y].position = sf::Vector2f(x,y);
                    }
                }
                if(position.x != 0 && position.y != 0){
                    xWidth += position.x;
                    yHeight += position.y;
                    for(int x=position.x;x<xWidth;++x){
                        for(int y=position.y;y<yHeight;++y){
                            (*destructible)[(yHeight-position.y)*(x-position.x)+(y-position.y)].position = sf::Vector2f(x,y);
                        }
                    }
                }
                return std::move(destructible);
            }
            ComponentFactory::ComponentFactory()
            : assets(std::make_shared<AssetManager>()){}
            ComponentFactory::ComponentFactory(std::shared_ptr<AssetManager> assets)
            : assets(assets){}
            bool ComponentFactory::loadAssets(const std::string& json){
                return assets->loadAssets(json);
            }
            bool ComponentFactory::unloadAssets(){
                return assets->clear();
            }
            void ComponentFactory::setAssetManager(std::shared_ptr<AssetManager> assets){
                this->assets = assets;
            }
            std::unique_ptr<baseComponent> ComponentFactory::createTransform(const sf::Vector2f& position,const sf::Vector2f& scale,const float& rotation){
                auto c = Utils::makeUniquePtr<Component<sf::Vector2f,sf::Vector2f,float>>(ComponentsMask::COMPONENT_TRANSFORM,position,scale,rotation);
                return std::move(c);
            }
            std::unique_ptr<baseComponent> ComponentFactory::createVelocity(const float& speed,const float& minSpeed,const float& maxSpeed){
                auto spd = speed;
                if(spd > maxSpeed){
                    spd = maxSpeed;
                }else if(spd < minSpeed){
                    spd = minSpeed;
                }
                auto c = Utils::makeUniquePtr<Component<sf::Vector2f,float,float,float>>(ComponentsMask::COMPONENT_VELOCITY,
                                                                                        sf::Vector2f(0,0),spd,minSpeed,maxSpeed);
                return std::move(c);
            }
            std::unique_ptr<baseComponent> ComponentFactory::createBounds(const sf::FloatRect& bounds){
                auto c = Utils::makeUniquePtr<Component<sf::FloatRect>>(ComponentsMask::COMPONENT_BOUNDS,bounds);
                return std::move(c);
            }
            std::unique_ptr<baseComponent> ComponentFactory::createDestructable(sf::Vector2f position,const std::string& imageID){
                sf::FloatRect bounds;
                auto destructable = mapImage(position,assets->getImage(imageID),&bounds);
                auto c = Utils::makeUniquePtr<Component<std::string,std::unique_ptr<sf::VertexArray>,sf::FloatRect>>(
                                            ComponentsMask::COMPONENT_DESTRUCTABLE,imageID,std::move(destructable),bounds);
                return std::move(c);
            }
            std::unique_ptr<baseComponent> ComponentFactory::createAnimation(const std::vector<std::string>& ids){
                auto compID = ComponentsMask::COMPONENT_ANIMATION;
                auto c = Utils::makeUniquePtr<Component<std::vector<std::string>>>(compID,ids);
                return std::move(c);
            }
            std::unique_ptr<baseComponent> ComponentFactory::createSprite(const std::string& id){
                auto c = Utils::makeUniquePtr<Component<std::string,std::unique_ptr<sf::Sprite>>>(
                            ComponentsMask::COMPONENT_SPRITE,id,Utils::makeUniquePtr<sf::Sprite>(assets->getTexture(id)));
                return std::move(c);
            }
            std::unique_ptr<baseComponent> ComponentFactory::createPassage(const sf::Vector2f& dest){
                auto c = Utils::makeUniquePtr<Component<sf::Vector2f>>(ComponentsMask::COMPONENT_PASSAGE,dest);
                return std::move(c);
            }
            std::unique_ptr<baseComponent> ComponentFactory::createIn(){
                auto c = Utils::makeUniquePtr<Component<>>(ComponentsMask::COMPONENT_IN);
                return std::move(c);
            }
            std::unique_ptr<baseComponent> ComponentFactory::createOut(){
                auto c = Utils::makeUniquePtr<Component<>>(ComponentsMask::COMPONENT_OUT);
                return std::move(c);
            }
            std::unique_ptr<baseComponent> ComponentFactory::createCounter(const int& count){
                auto c = Utils::makeUniquePtr<Component<int>>(ComponentsMask::COMPONENT_COUNT,count);
                return std::move(c);
            }
}
