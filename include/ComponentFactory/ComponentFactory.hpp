#ifndef COMPONENT_FACTORY_H
#define COMPONENT_FACTORY_H
#include <AssetManager/AssetManager.hpp>
#include <Components/Component.hpp>
namespace ant{
    class ComponentFactory{
        private:
            std::shared_ptr<AssetManager> assets;
        public:
            ComponentFactory();
            void setAssetManager(std::shared_ptr<AssetManager> assets);
            inline std::shared_ptr<AssetManager> getAssetManager(){ return this->assets; }

            std::unique_ptr<baseComponent> createTransform(sf::Vector2f position,int rotation);
            std::unique_ptr<baseComponent> createBounds(sf::FloatRect bounds);


            ~ComponentFactory();
    };
}

#endif // COMPONENT_FACTORY_H
