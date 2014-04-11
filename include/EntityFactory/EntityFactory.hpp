#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H
#include <ComponentFactory/ComponentFactory.hpp>
#include <Components/ComponentMask.hpp>
#include <ComponentSettings/ComponentSettings.hpp>
#include <Entity/Entity.hpp>

namespace ant{
    /**
     * Clase para crear las entidades del juego.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class EntityFactory{
        private:
            std::shared_ptr<ComponentFactory> componentFactory;
        public:
                static const long int Ant = ComponentsMask::COMPONENT_VELOCITY
                               | ComponentsMask::COMPONENT_SPRITE
                               | ComponentsMask::COMPONENT_TRANSFORM;
                static const long int AntQueen = ComponentsMask::COMPONENT_VELOCITY
                                    | ComponentsMask::COMPONENT_SPRITE
                                    | ComponentsMask::COMPONENT_TRANSFORM
                                    | ComponentsMask::COMPONENT_EGGS;
                static const long int Nest = ComponentsMask::COMPONENT_DESTRUCTABLE
                                | ComponentsMask::COMPONENT_SPRITE;
                static const long int Battlefield = ComponentsMask::COMPONENT_SPRITE;
            EntityFactory();
            EntityFactory(const std::string& json);
            bool loadAssets(const std::string& json);
            bool unloadAssets();
            void setAssetManager(std::shared_ptr<AssetManager> assets);
            inline std::shared_ptr<AssetManager> getAssetManager(){ return componentFactory->getAssetManager(); }
            std::unique_ptr<Entity> createEntity(long int mask);
            std::unique_ptr<Entity> createEntity(long int mask, ComponentSettings& cs);
            void setComponentFactory(std::shared_ptr<ComponentFactory> cf);
            inline std::shared_ptr<ComponentFactory> getComponentFactory(){ return this->componentFactory; }
            ~EntityFactory();
    };
}

#endif // ENTITY_FACTORY_H
