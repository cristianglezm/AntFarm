#ifndef WORLD_H
#define WORLD_H
#include <SFML/System/Time.hpp>
#include <memory>
#include <EntityManager/EntityManager.hpp>
#include <SystemManager/SystemManager.hpp>
namespace ant{
    class World{
        private:
            std::unique_ptr<SystemManager> systemManager;
            std::shared_ptr<EntityManager> entityManager;
            std::shared_ptr<EventQueue> eventQueue;
        public:
            World();
            World(std::shared_ptr<EntityManager> entityManager,std::unique_ptr<SystemManager> systemManager,std::shared_ptr<EventQueue> eventQueue);
            void setEntityManager(std::shared_ptr<EntityManager> entityManager);
            inline std::shared_ptr<EntityManager> getEntityManager(){ return this->entityManager; }
            void setSystemManager(std::unique_ptr<SystemManager> systemManager);
            inline SystemManager* getSystemManager(){ return this->systemManager.get(); }
            void setEventQueue(std::shared_ptr<EventQueue> eventQueue);
            inline std::shared_ptr<EventQueue> getEventQueue(){ return this->eventQueue; }
            void update(sf::Time dt);
            void render();
            ~World();
    };
}
#endif // WORLD_H
