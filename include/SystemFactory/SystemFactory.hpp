#ifndef SYSTEM_FACTORY_H
#define SYSTEM_FACTORY_H
#include <memory>
#include <EntityManager/EntityManager.hpp>
#include <GameEventDispatcher/GameEventDispatcher.hpp>
#include <EventQueue/EventQueue.hpp>
#include <Systems/collisionSystem/collisionSystem.hpp>
#include <Systems/renderSystem/renderSystem.hpp>
#include <Systems/diggingSystem/diggingSystem.hpp>
#include <Systems/movementSystem/movementSystem.hpp>
#include <Systems/inputSystem/inputSystem.hpp>
namespace ant{
    class SystemFactory{
        private:
            std::shared_ptr<GameEventDispatcher> gameEventDispatcher;
            std::shared_ptr<EventQueue> eventQueue;
        public:
            SystemFactory();
            SystemFactory(std::shared_ptr<GameEventDispatcher> ged,std::shared_ptr<EventQueue> eq);
            void setEventQueue(std::shared_ptr<EventQueue> eq);
            inline std::shared_ptr<EventQueue> getEventQueue(){ return eventQueue; }
            void setGameEventDispatcher(std::shared_ptr<GameEventDispatcher> ged);
            inline std::shared_ptr<GameEventDispatcher> getGameEventDispatcher(){ return gameEventDispatcher; }
            std::shared_ptr<renderSystem> createRenderSystem();
            std::shared_ptr<inputSystem> createInputSystem();
            std::shared_ptr<collisionSystem> createCollisionSystem(sf::FloatRect bounds);
            std::shared_ptr<movementSystem> createMovementSystem();
            ~SystemFactory();
    };
}
#endif // SYSTEM_FACTORY_H
