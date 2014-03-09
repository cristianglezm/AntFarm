#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include <list>
#include <algorithm>
#include <memory>
#include <Entity/Entity.hpp>
namespace ant{
    class EntityManager{
        private:
            std::list<std::unique_ptr<Entity> > entities;
        public:
            EntityManager();
            void addEntity(std::unique_ptr<Entity> e);
            void removeEntity(std::unique_ptr<Entity> e);
            void removeEntity(std::string name);
            std::unique_ptr<Entity>& getEntity(std::string name);
            void addEntities(std::list<std::unique_ptr<Entity> > e);
            inline std::list<std::unique_ptr<Entity> >& getEntities(){ return this->entities; }
            std::unique_ptr<Entity> Transfer(std::string name);
            ~EntityManager();
    };
};
#endif // ENTITY_MANAGER_H
