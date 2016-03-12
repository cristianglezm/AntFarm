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

#ifndef WORLD_MANAGER_H
#define WORLD_MANAGER_H
#include <World/World.hpp>
#include <map>
#include <memory>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
namespace ant{
    /**
     * @brief Clase Contenedor para los mundos
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class WorldManager{
        public:
            /**
             * @brief Contenedor usado por WorldManager
             */
            using map = std::map<long int,std::unique_ptr<World>>;
            /**
             * @brief Iterador del Contenedor
             */
            using iterator = map::iterator;
            /**
             * @brief Constructor por defecto
             */
            WorldManager();
            /**
             * @brief Añade un World al contenedor.
             * @param w std::unique_ptr<World>
             */
            void addWorld(std::unique_ptr<World> w);
            /**
             * @brief Obtiene un "naked Pointer" del mundo especificado.
             *        Si no se encuentra devuelve un nullptr.
             * @param id long int id del mundo
             * @return World *
             */
            World* getWorld(long int id);
            /**
             * @brief Elimina el mundo especificado.
             * @param id long int
             */
            void removeWorld(long int id);
            /**
             * @brief Devuelve el contendor usado.
             * @return map
             */
            inline map& getWorlds(){ return this->worlds; }
            /**
             * @brief Establece el contenedor.
             * @param worlds map
             */
            void setWorlds(map worlds);
            /**
             * @brief Actualiza el mundo especificado por id.
             *
             * Si se pone -1 actualiza a todos los mundos que contenga.
             *
             * @param id long int id del mundo (-1 para actualizar todos)
             * @param dt sf::Time delta time
             */
            void update(long int id,sf::Time dt);
            /**
             * @brief Devuelve el numero de mundos que tiene.
             */
            inline int size(){ return worlds.size(); }
            /**
             * @brief Renderiza el mundo especificado por el id.
             *
             * Si se pone -1 Renderizara todos los mundos, en pantalla se vera el ultimo.
             *
             * @param id long int id del mundo (-1 para renderizar a todos)
             * @param win sf::RenderWindow & ventana a la cual dibujar.
             */
            void render(long int id,sf::RenderWindow& win);
            /**
             * @brief Limpia los mundos que contiene.
             */
            void clear();
            ~WorldManager() = default;
        private:
            map worlds;
    };
}
#endif // WORLD_MANAGER_H
