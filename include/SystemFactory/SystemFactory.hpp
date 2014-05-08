#ifndef SYSTEM_FACTORY_H
#define SYSTEM_FACTORY_H
#include <memory>
#include <EntityManager/EntityManager.hpp>
#include <GameEventDispatcher/GameEventDispatcher.hpp>
#include <EventQueue/EventQueue.hpp>
#include <Systems/collisionSystem/collisionSystem.hpp>
#include <Systems/renderSystem/renderSystem.hpp>
#include <Systems/constructorSystem/constructorSystem.hpp>
#include <Systems/movementSystem/movementSystem.hpp>
#include <Systems/spawnSystem/spawnSystem.hpp>
#include <Systems/inputSystem/inputSystem.hpp>
namespace ant{
    /**
     * @brief Clase para crear sistemas.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class SystemFactory{
        public:
            /**
             * @brief Constructor por defecto.
             */
            SystemFactory();
            /**
             * @brief Constructor para compartir la misma cola y suscritor de eventos.
             * @param ged std::shared_ptr<GameEventDispatcher>
             * @param eq std::shared_ptr<EventQueue>
             */
            SystemFactory(std::shared_ptr<GameEventDispatcher> ged,std::shared_ptr<EventQueue> eq);
            /**
             * @brief Setter para la cola de eventos.
             * @param eq std::shared_ptr<EventQueue>
             */
            void setEventQueue(std::shared_ptr<EventQueue> eq);
            /**
             * @brief Getter para la cola de eventos.
             * @return std::shared_ptr<EventQueue>
             */
            inline std::shared_ptr<EventQueue> getEventQueue(){ return eventQueue; }
            /**
             * @brief Setter para el suscritor de eventos.
             * @param ged std::shared_ptr<GameEventDispatcher>
             */
            void setGameEventDispatcher(std::shared_ptr<GameEventDispatcher> ged);
            /**
             * @brief Getter para el suscritor de eventos.
             * @return std::shared_ptr<GameEventDispatcher>
             */
            inline std::shared_ptr<GameEventDispatcher> getGameEventDispatcher(){ return gameEventDispatcher; }
            /**
             * @brief Crea un sistema de renderizado.
             *
             * @return std::shared_ptr<renderSystem>
             */
            std::shared_ptr<renderSystem> createRenderSystem();
            /**
             * @brief Crea un sistema de input
             * @return std::shared_ptr<inputSystem>
             */
            std::shared_ptr<inputSystem> createInputSystem();
            /**
             * @brief Crea un sistema de colision.
             * @param bounds sf::FloatRect rectangulo para zona que ocupa.
             * @return std::shared_ptr<collisionSystem>
             */
            std::shared_ptr<collisionSystem> createCollisionSystem(sf::FloatRect bounds);
            /**
             * @brief Crea un sistema de movimiento.
             * @see movementSystem::movementSystem
             * @return std::shared_ptr<movementSystem>
             */
            std::shared_ptr<movementSystem> createMovementSystem();
            /**
             * @brief Crea un sistema de creacion de entidades.
             * @see spawnSystem::spawnSystem
             * @return std::shared_ptr<spawnSystem>
             */
            std::shared_ptr<spawnSystem> createSpawnSystem(int nEntities,EntityFactory* ef,sf::Time ot,sf::Vector2f spawnPoint);

            ~SystemFactory();
        private:
            std::shared_ptr<GameEventDispatcher> gameEventDispatcher;
            std::shared_ptr<EventQueue> eventQueue;
    };
}
#endif // SYSTEM_FACTORY_H
