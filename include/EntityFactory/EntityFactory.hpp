#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H
#include <ComponentFactory/ComponentFactory.hpp>
#include <Components/ComponentMask.hpp>

namespace ant{
    class EntityFactory{
        private:
            std::shared_ptr<ComponentFactory> componentFactory;
        public:
                long int Ant = ComponentsMask::COMPONENT_MOVEMENT
                               | ComponentsMask::COMPONENT_SPRITE
                               | ComponentsMask::COMPONENT_TRANSFORM;
                long int AntQueen = ComponentsMask::COMPONENT_MOVEMENT
                                    | ComponentsMask::COMPONENT_SPRITE
                                    | ComponentsMask::COMPONENT_TRANSFORM
                                    | ComponentsMask::COMPONENT_EGGS;
                long int Nest = ComponentsMask::COMPONENT_DESTRUCTABLE
                                | ComponentsMask::COMPONENT_SPRITE;
                long int Battlefield = ComponentsMask::COMPONENT_SPRITE;
            EntityFactory();
            createEntity(long int mask);

            ~EntityFactory();
    };
}

#endif // ENTITY_FACTORY_H
