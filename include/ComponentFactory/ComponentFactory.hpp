#ifndef COMPONENT_FACTORY_H
#define COMPONENT_FACTORY_H
#include <AssetManager/AssetManager.hpp>
#include <Components/SpriteComponent/SpriteComponent.hpp>
#include <Components/DestructableComponent/DestructableComponent.hpp>
namespace ant{
    class ComponentFactory{
        private:
            std::shared_ptr<AssetManager> assets;
        public:
            ComponentFactory();
            void setAssetManager(std::shared_ptr<AssetManager> assets);
            inline std::shared_ptr<AssetManager> getAssetManager(){ return this->assets; }
            ~ComponentFactory();
    };
}

#endif // COMPONENT_FACTORY_H
