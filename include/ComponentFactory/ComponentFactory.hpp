#ifndef COMPONENT_FACTORY_H
#define COMPONENT_FACTORY_H
#include <SFML/Graphics.hpp>
#include <array>
#include <AssetManager/AssetManager.hpp>
#include <Components/Component.hpp>
#include <Components/ComponentMask.hpp>
namespace ant{
    /**
     *
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class ComponentFactory{
        private:
            std::shared_ptr<AssetManager> assets;
            std::unique_ptr<sf::VertexArray> mapImage(const sf::Vector2f& position,sf::Image& img);
        public:
            ComponentFactory();
            ComponentFactory(std::shared_ptr<AssetManager> assets);
            bool loadAssets(const std::string& json);
            bool unloadAssets();
            void setAssetManager(std::shared_ptr<AssetManager> assets);
            inline std::shared_ptr<AssetManager> getAssetManager(){ return this->assets; }

            std::unique_ptr<baseComponent> createTransform(sf::Vector2f position,sf::Vector2f scale,float rotation);
            std::unique_ptr<baseComponent> createVelocity(sf::Vector2f velocity,float speed,float minSpeed,float maxSpeed);
            std::unique_ptr<baseComponent> createBounds(sf::FloatRect bounds);
            std::unique_ptr<baseComponent> createDestructable(sf::Vector2f position,const std::string& imageID);
            std::unique_ptr<baseComponent> createAnimation(std::vector<std::string> ids);
            std::unique_ptr<baseComponent> createSprite(std::string id);

            ~ComponentFactory();
    };
}

#endif // COMPONENT_FACTORY_H
