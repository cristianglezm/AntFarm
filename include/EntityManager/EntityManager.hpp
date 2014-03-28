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
            typedef std::list<std::unique_ptr<Entity>>::iterator iterator;
            EntityManager();
            void addEntity(std::unique_ptr<Entity> e);
            void removeEntity(std::unique_ptr<Entity>& e);
            iterator removeEntity(const std::string& name);
            iterator removeEntity(iterator it);
            Entity* getEntity(const std::string& name);
            void addEntities(std::list<std::unique_ptr<Entity> > e);
            inline std::list<std::unique_ptr<Entity> >& getEntities(){ return this->entities; }
            std::unique_ptr<Entity> Transfer(const std::string& name);
            ~EntityManager();
    };
};
#endif // ENTITY_MANAGER_H
