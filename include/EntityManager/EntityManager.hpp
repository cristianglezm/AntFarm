#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include <Entity/Entity.hpp>
#include <vector>
#include <algorithm>
namespace ant{
    class EntityManager{
        private:
            std::vector<Entity> entities;
        public:
            EntityManager();
            void addEntity(Entity e);
            void removeEntity(Entity e);
            Entity getEntity(std::string name);
            void addEntities(std::vector<Entity> e);
            inline std::vector<Entity> getEntities(){ return this->entities; }
            ~EntityManager();
    };
};
#endif // ENTITY_MANAGER_H
