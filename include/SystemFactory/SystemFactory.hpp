////////////////////////////////////////////////////////////////
// Copyright 2014 Cristian Glez <Cristian.glez.m@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
////////////////////////////////////////////////////////////////

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
#include <Systems/gravitySystem/gravitySystem.hpp>
#include <Systems/spawnSystem/spawnSystem.hpp>
#include <Systems/outSystem/outSystem.hpp>
namespace ant{
    /**
     * @brief Clase para crear sistemas.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class SystemFactory final{
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
             * @brief Crea un sistema de colision.
             * @param GameMap sf::VertexArray * Terreno del juego.
             * @param bounds sf::FloatRect rectangulo para zona que ocupa.
             * @return std::shared_ptr<collisionSystem>
             */
            std::shared_ptr<collisionSystem> createCollisionSystem(sf::FloatRect bounds,sf::VertexArray * GameMap);
            /**
             * @brief Crea un sistema de movimiento.
             * @see movementSystem::movementSystem
             * @return std::shared_ptr<movementSystem>
             */
            std::shared_ptr<movementSystem> createMovementSystem();
            /**
             * @brief Crea un sistema de gravedad
             * @see gravitySystem::gravitySystem
             * @param gravity float
             * @return std::shared_ptr<gravitySystem>
             */
            std::shared_ptr<gravitySystem> createGravitySystem(float gravity);
            /**
             * @brief Crea un sistema de creacion de entidades.
             * @see spawnSystem::spawnSystem
             * @return std::shared_ptr<spawnSystem>
             */
            std::shared_ptr<spawnSystem> createSpawnSystem(int nEntities,EntityFactory* ef,sf::Time ot,sf::Vector2f spawnPoint,long int state);
            /**
             * @brief Crea un sistema de construccion.
             * @see constructorSystem::constructorSystem
             * @return std::shared_ptr<constructorSystem>
             */
            std::shared_ptr<constructorSystem> createConstructorSystem(sf::VertexArray* GameMap,sf::FloatRect bounds);
            /**
             * @brief Crea un sistema para comprobar cuando salen del mapa o entran por alguna entidad que tenga Component_OUT
             * @see outSystem::outSystem
             * @return std::shared_ptr<outSystem>
             */
            std::shared_ptr<outSystem> createOutSystem(int totalEntities);
            ~SystemFactory();
        private:
            std::shared_ptr<GameEventDispatcher> gameEventDispatcher;
            std::shared_ptr<EventQueue> eventQueue;
    };
}
#endif // SYSTEM_FACTORY_H
