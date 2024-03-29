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

#ifndef LEVEL_H
#define LEVEL_H
#include <memory>
#include <SFML/System/Time.hpp>
#include <Utils/String.hpp>
#include <JsonBox.h>
#include <WorldManager.hpp>
#include <WorldFactory.hpp>
#include <EventQueue.hpp>
#include <EntityFactory.hpp>
#include <Config.hpp>

namespace ant{
    /**
     * @brief Clase que tiene el nivel del juego
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class Level final{
        public:
            /**
             * @brief Constructor principal
             *
             * @param assetsFilename std::string fichero json a cargar.
             *        formato: AssetManager::loadAssets()
             * @param bounds sf::FloatRect rectangulo con los limites del nivel.
             * @param ged std::shared_ptr<GameEventDispatcher> para que se suscriban a los eventos.
             */
            Level(const std::string& assetsFilename,sf::FloatRect bounds,std::shared_ptr<GameEventDispatcher> ged);
            /**
             * @brief Constructor secundario
             * @param am std::shared_ptr<AssetManager>
             * @param bounds sf::FloatRect rectangulo con los limites del nivel.
             * @param ged std::shared_ptr<GameEventDispatcher> para que se suscriban a los eventos.
             */
            Level(std::shared_ptr<AssetManager> am,sf::FloatRect bounds,std::shared_ptr<GameEventDispatcher> ged);
            /**
             * @brief Inicializa el nivel.
             *
             * Añade los mundos iniciales al nivel.
             * @param bounds sf::FloatRect rectangulo con los limites del nivel.
             */
            void init(const sf::FloatRect& bounds);
            /**
             * @brief Carga el nivel de un fichero json.
             * @return bool
             */
            bool loadLevel(const sf::FloatRect& bounds, const std::string& filename);
            /**
             * @brief Setter para la cola de eventos.
             * @param id level id
             * @param eq std::shared_ptr<EventQueue> Cola para que los sistemas añadan los eventos que sucenden en el juego.
             */
            void setEventQueue(std::size_t id, std::shared_ptr<EventQueue> eq);
            /**
             * @brief Getter para la cola de eventos
             * @return std::shared_ptr<EventQueue> Devuelve la cola de eventos.
             */
            inline std::shared_ptr<EventQueue> getEventQueue(std::size_t id) noexcept{ return this->eventQueues[id]; }
            /**
             * @brief adds a event queue
             * @param eq EventQueue
             */
            void addEventQueue(std::shared_ptr<EventQueue> eq);
            /**
             * @brief adds a GameEventDispatcher
             * @param ged GameEventDispatcher
             */
            void addGameEventDispatcher(std::shared_ptr<GameEventDispatcher> ged);
            /**
             * @brief changes a GameEventDispatcher
             * @param id world id
             * @param ged GameEventDispatcher
             */
            void setGameEventDispatcher(std::size_t id,std::shared_ptr<GameEventDispatcher> ged);
            /**
             * @brief Getter for GameEventDispatcher
             * @param id
             * @return std::shared_ptr<GameEventDispatcher>
             */
            inline std::shared_ptr<GameEventDispatcher> getGameEventDispatcher(std::size_t id) noexcept{ return gameEventDispatchers[id]; }
            /**
             * @brief Setter para la fabrica de mundos.
             * @param wf std::shared_ptr<WorldFactory>
             */
            void setWorldFactory(std::shared_ptr<WorldFactory> wf);
            /**
             * @brief Getter de la fabrica de mundos.
             * @return std::shared_ptr<WorldFactory>
             */
            inline std::shared_ptr<WorldFactory> getWorldFactory() noexcept{ return worldFactory; }
            /**
             * @brief Setter para el AssetManager
             * @param assets std::shared_ptr<AssetManager>
             */
             void setAssetManager(std::shared_ptr<AssetManager> assets);
            /**
             * @brief Getter para el AssetManager
             * @return std::shared_ptr<AssetManager>
             */
             inline std::shared_ptr<AssetManager> getAssetManager() noexcept{ return worldFactory->getAssetManager(); }
             /**
              * @brief Devuelve el numero total de niveles que tiene.
              * @return std::size_t number of levels.
              */
             inline std::size_t size(){ return levels->size(); }
            /**
             * @brief Actualiza el mundo especificado.
             *
             * Actualiza el mundo especificado, si se pone un -1 se actualizaran todos.
             * @param id int Mundo a actualizar
             * @param dt sf::Time delta time.
             */
            void update(int id,sf::Time dt);
            /**
             * @brief Renderiza el mundo especificado.
             *
             * @param id int Mundo a actualizar
             * @param win sf::RenderWindow & ventana a la cual dibujar.
             */
            void render(int id,sf::RenderWindow& win);
            ~Level() = default;
        private:
            std::shared_ptr<WorldManager> levels;
            std::vector<std::shared_ptr<EventQueue>> eventQueues;
            std::vector<std::shared_ptr<GameEventDispatcher>> gameEventDispatchers;
            std::shared_ptr<WorldFactory> worldFactory;
    };
}

#endif // LEVEL_H
