#include <ComponentFactory.hpp>

namespace ant{
    std::unique_ptr<sf::VertexArray> ComponentFactory::mapImage(const sf::Vector2f& position,sf::Image& img,sf::FloatRect* bounds){
        unsigned int xWidth = img.getSize().x;
        unsigned int yHeight = img.getSize().y;
        bounds->height = yHeight;
        bounds->width = xWidth;
        bounds->left = position.x;
        bounds->top = position.y;
        auto destructible = std::make_unique<sf::VertexArray>(sf::Points,xWidth*yHeight);
        // map the image to vertexArray
        for(auto x=0u;x<xWidth;++x){
            for(auto y=0u;y<yHeight;++y){
                (*destructible)[yHeight*x+y].color = img.getPixel(x,y);
                (*destructible)[yHeight*x+y].position = sf::Vector2f(x,y);
            }
        }
        // set the position for the image
        if(position.x != 0 && position.y != 0){
            xWidth += position.x;
            yHeight += position.y;
            for(unsigned int x=position.x;x<xWidth;++x){
                for(unsigned int y=position.y;y<yHeight;++y){
                    (*destructible)[(yHeight-position.y)*(x-position.x)+(y-position.y)].position = sf::Vector2f(x,y);
                }
            }
        }
        return destructible;
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
        auto c = std::make_unique<ComponentsAlias::transform>(ComponentsMask::COMPONENT_TRANSFORM,position,scale,rotation);
        return std::move(c);
    }
    std::unique_ptr<baseComponent> ComponentFactory::createVelocity(const float& speed,const float& minSpeed,const float& maxSpeed){
        auto spd = speed;
        if(spd > maxSpeed){
            spd = maxSpeed;
        }else if(spd < minSpeed){
            spd = minSpeed;
        }
        auto c = std::make_unique<ComponentsAlias::velocity>(ComponentsMask::COMPONENT_VELOCITY,
                                                                    sf::Vector2f(0,0),spd,minSpeed,maxSpeed);
        return c;
    }
    std::unique_ptr<baseComponent> ComponentFactory::createBounds(const sf::FloatRect& bounds){
        auto c = std::make_unique<ComponentsAlias::bounds>(ComponentsMask::COMPONENT_BOUNDS,bounds);
        return c;
    }
    std::unique_ptr<baseComponent> ComponentFactory::createDestructable(sf::Vector2f position,const std::string& imageID){
        sf::FloatRect bounds;
        auto destructable = mapImage(position,assets->getImage(imageID),&bounds);
        auto c = std::make_unique<ComponentsAlias::destructable>(
                                    ComponentsMask::COMPONENT_DESTRUCTABLE,imageID,std::move(destructable),bounds);
        return c;
    }
    std::unique_ptr<baseComponent> ComponentFactory::createAnimation(const std::vector<std::string>& ids){
        auto compID = ComponentsMask::COMPONENT_ANIMATION;
        auto c = std::make_unique<ComponentsAlias::animation>(compID,ids);
        return c;
    }
    std::unique_ptr<baseComponent> ComponentFactory::createSprite(const std::string& id){
        auto c = std::make_unique<ComponentsAlias::sprite>(
                    ComponentsMask::COMPONENT_SPRITE,id,std::make_unique<sf::Sprite>(assets->getTexture(id)));
        return c;
    }
    std::unique_ptr<baseComponent> ComponentFactory::createPassage(const sf::Vector2f& dest){
        auto c = std::make_unique<ComponentsAlias::passage>(ComponentsMask::COMPONENT_PASSAGE,dest);
        return c;
    }
    std::unique_ptr<baseComponent> ComponentFactory::createIn(){
        auto c = std::make_unique<ComponentsAlias::in>(ComponentsMask::COMPONENT_IN);
        return c;
    }
    std::unique_ptr<baseComponent> ComponentFactory::createOut(){
        auto c = std::make_unique<ComponentsAlias::out>(ComponentsMask::COMPONENT_OUT);
        return c;
    }
    std::unique_ptr<baseComponent> ComponentFactory::createCounter(const int& count){
        auto c = std::make_unique<ComponentsAlias::count>(ComponentsMask::COMPONENT_COUNT,count);
        return c;
    }
}