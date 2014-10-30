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

#ifndef WORLD_H
#define WORLD_H
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <Utils/Utility.hpp>
#include <EntityManager/EntityManager.hpp>
#include <SystemManager/SystemManager.hpp>
#include <GameEventDispatcher/GameEventDispatcher.hpp>
namespace ant{
    /**
     * @brief Clase para crear escenarios.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class World final{
        public:
            /**
             * @brief Constructor por defecto.
             */
            World();
            /**
             * @brief Constructor con el id del World.
             * @param id long int id para este World.
             */
            World(long int id);
            /**
             * @brief Constructor con el id del World, EntityManager,SystemManager y EventQueue
             * @param id long int id del mundo
             * @param eM std::shared_ptr<EntityManager>
             * @param sM std::shared_ptr<SystemManager>
             * @param eQ std::shared_ptr<EventQueue>
             */
            World(long int id,std::shared_ptr<EntityManager> eM,std::unique_ptr<SystemManager> sM,std::shared_ptr<EventQueue> eQ);
            /**
             * @brief Setter para el EntityManager
             * @param eM std::shared_ptr<EntityManager>
             */
            void setEntityManager(std::shared_ptr<EntityManager> eM);
            /**
             * @brief Getter para el EntityManager
             * @return std::shared_ptr<EntityManager>
             */
            inline std::shared_ptr<EntityManager> getEntityManager(){ return this->entityManager; }
            /**
             * @brief Setter para el SystemManager
             * @param sM std::unique_ptr<SystemManager>
             */
            void setSystemManager(std::unique_ptr<SystemManager> sM);
            /**
             * @brief Getter para el SystemManager
             * @return SystemManager *
             */
            inline SystemManager* getSystemManager(){ return this->systemManager.get(); }
            /**
             * @brief Setter para la EventQueue
             * @param eQ std::shared_ptr<EventQueue>
             */
            void setEventQueue(std::shared_ptr<EventQueue> eQ);
            /**
             * @brief Getter para el EventQueue
             * @return std::shared_ptr<EventQueue>
             */
            inline std::shared_ptr<EventQueue> getEventQueue(){ return this->eventQueue; }
            /**
             * @brief Setter para el GameEventDispatcher
             * @param ged std::shared_ptr<GameEventDispatcher>
             */
            void setGameEventDispatcher(std::shared_ptr<GameEventDispatcher> ged);
            /**
             * @brief Getter para el GameEventDispatcher
             * @return std::shared_ptr<GameEventDispatcher>
             */
            inline std::shared_ptr<GameEventDispatcher> getGameEventDispatcher(){ return this->gameEventDispatcher; }
            /**
             * @brief Setter para el id del mundo.
             * @param id long int
             */
            void setId(long int id);
            /**
             * @brief Getter del id del mundo
             * @return const long
             */
            inline const long& getId() const { return id; }
            /**
             * @brief Actualiza todas las entidades del EntityManager con los sistemas que tenga en su SystemManager
             * @param dt sf::Time delta time
             */
            void update(const sf::Time& dt);
            /**
             * @brief Renderiza todas las entidades del EntityManager que tengan los componentes necesarios.
             * @param win sf::RenderWindow &
             */
            void render(sf::RenderWindow& win);
        private:
            long int id;
            std::shared_ptr<EventQueue> eventQueue;
            std::shared_ptr<EntityManager> entityManager;
            std::unique_ptr<SystemManager> systemManager;
            std::shared_ptr<GameEventDispatcher> gameEventDispatcher;
    };
}
#endif // WORLD_H
