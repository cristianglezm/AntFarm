#ifndef COMPONENT_FACTORY_H
#define COMPONENT_FACTORY_H
#include <SFML/Graphics.hpp>

#include <AssetManager/AssetManager.hpp>
#include <Components/Component.hpp>
#include <Components/ComponentMask.hpp>
namespace ant{
    class ComponentFactory{
        private:
            std::shared_ptr<AssetManager> assets;
            mapImage(const sf::Vector2f& position,sf::VertexArray& toMap,sf::Image& img);
        public:
            ComponentFactory();
            ComponentFactory(std::shared_ptr<AssetManager> assets);
            void setAssetManager(std::shared_ptr<AssetManager> assets);
            inline std::shared_ptr<AssetManager> getAssetManager(){ return this->assets; }

            std::unique_ptr<baseComponent> createTransform(sf::Vector2f position,sf::Vector2f scale,float rotation);
            std::unique_ptr<baseComponent> createBounds(sf::FloatRect bounds);
            std::unique_ptr<baseComponent> createDestructable(sf::Vector2f position,const std::string& imageID);
            std::unique_ptr<baseComponent> createSprite(std::string id);

            ~ComponentFactory();
    };
}

#endif // COMPONENT_FACTORY_H
