#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H
#include <ComponentFactory/ComponentFactory.hpp>

namespace ant{
    class EntityFactory{
        private:
            std::shared_ptr<ComponentFactory> componentFactory;
        public:
            EntityFactory();

            ~EntityFactory();
    };
}

#endif // ENTITY_FACTORY_H
