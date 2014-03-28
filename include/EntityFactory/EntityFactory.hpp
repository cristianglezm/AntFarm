#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H
#include <ComponentFactory/ComponentFactory.hpp>
#include <Components/ComponentMask.hpp>
#include <ComponentSettings/ComponentSettings.hpp>
#include <Entity/Entity.hpp>

namespace ant{
    class EntityFactory{
        private:
            std::shared_ptr<ComponentFactory> componentFactory;
        public:
                static const long int Ant = ComponentsMask::COMPONENT_MOVEMENT
                               | ComponentsMask::COMPONENT_SPRITE
                               | ComponentsMask::COMPONENT_TRANSFORM;
                static const long int AntQueen = ComponentsMask::COMPONENT_MOVEMENT
                                    | ComponentsMask::COMPONENT_SPRITE
                                    | ComponentsMask::COMPONENT_TRANSFORM
                                    | ComponentsMask::COMPONENT_EGGS;
                static const long int Nest = ComponentsMask::COMPONENT_DESTRUCTABLE
                                | ComponentsMask::COMPONENT_SPRITE;
                static const long int Battlefield = ComponentsMask::COMPONENT_SPRITE;
            EntityFactory();
            EntityFactory(std::string json_filename);
            void createEntity(long int mask);
            void createEntity(long int mask, ComponentSettings& cs);
            void setComponentFactory(std::shared_ptr<ComponentFactory> cf);
            inline std::shared_ptr<ComponentFactory> getComponentFactory(){ return this->componentFactory; }
            ~EntityFactory();
    };
}

#endif // ENTITY_FACTORY_H
