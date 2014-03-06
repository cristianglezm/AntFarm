#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include <Entity/Entity.hpp>
#include <list>
#include <algorithm>
#include <memory>
namespace ant{
    class EntityManager{
        private:
            std::list<std::unique_ptr<Entity> > entities;
        public:
            EntityManager();
            void addEntity(Entity e);
            void removeEntity(Entity e);
            Entity getEntity(std::string name);
            void addEntities(std::list<std::unique_ptr<Entity> > e);
            inline std::list<std::unique_ptr<Entity> > getEntities(){ return this->entities; }
            ~EntityManager();
    };
};
#endif // ENTITY_MANAGER_H
