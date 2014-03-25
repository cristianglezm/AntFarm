#ifndef WORLD_H
#define WORLD_H
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <EntityManager/EntityManager.hpp>
#include <SystemManager/SystemManager.hpp>
#include <GameEventDispatcher/GameEventDispatcher.hpp>
namespace ant{
    class World{
        private:
            std::unique_ptr<SystemManager> systemManager;
            std::shared_ptr<EntityManager> entityManager;
            std::shared_ptr<EventQueue> eventQueue;
            std::shared_ptr<GameEventDispatcher> gameEventDispatcher;
            long int id;
        public:
            World();
            World(long int id);
            World(long int id,std::shared_ptr<EntityManager> entityManager,std::unique_ptr<SystemManager> systemManager,std::shared_ptr<EventQueue> eventQueue);
            void setEntityManager(std::shared_ptr<EntityManager> entityManager);
            inline std::shared_ptr<EntityManager> getEntityManager(){ return this->entityManager; }
            void setSystemManager(std::unique_ptr<SystemManager> systemManager);
            inline SystemManager* getSystemManager(){ return this->systemManager.get(); }
            void setEventQueue(std::shared_ptr<EventQueue> eventQueue);
            inline std::shared_ptr<EventQueue> getEventQueue(){ return this->eventQueue; }
            void setGameEventDispatcher(std::shared_ptr<GameEventDispatcher> ged);
            inline std::shared_ptr<GameEventDispatcher> getGameEventDispatcher(){ return this->gameEventDispatcher; }
            void setId(long int id);
            inline long int getId(){ return id; }
            void update(sf::Time dt);
            void render(sf::RenderWindow& win);
            ~World();
    };
}
#endif // WORLD_H
