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

#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H
#include <map>
#include <memory>
#include <Systems/System.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace ant{
    /**
     * @brief Clase contenedor para los systemas.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class SystemManager final{
        public:
            /**
             * @brief Contenedor usado por la clase.
             */
            typedef std::map<std::string,std::shared_ptr<System>> container;
            /**
             * @brief Constructor por defecto.
             */
            SystemManager();
            /**
             * @brief Añade un sistema al manager.
             * @param s std::shared_ptr<System>
             * @return bool
             */
            bool addSystem(std::shared_ptr<System> s);
            /**
             * @brief Devuelve el sistema con el nombre especificado.
             * @param name std::string nombre del sistema.
             * @return std::shared_ptr<System>
             */
            std::shared_ptr<System> getSystem(const std::string& name);
            /**
             * @brief Setter para poner el contenedor con todos los sistemas.
             * @param systems container
             */
            void setSystems(container systems);
            /**
             * @brief Getter para obtener el contenedor de los sistemas.
             * @return SystemManager::container
             */
            inline SystemManager::container& getSystems(){ return systems; }
            /**
             * @brief Elimina el sistema del manager.
             * @param name std::string nombre del sistema.
             */
            void removeSystem(const std::string& name);
            /**
             * @brief Establece el mismo EntityManager a todos los sistemas que esten agregados.
             * @param entityManager std::shared_ptr<EntityManager>
             */
            void setEntityManager(std::shared_ptr<EntityManager> entityManager);
            /**
             * @brief Establece la misma EventQueue a todos los sistemas que esten agregados.
             * @param eventQueue std::shared_ptr<EventQueue>
             */
            void setEventQueue(std::shared_ptr<EventQueue> eventQueue);
            /**
             * @brief Hace que todos los sistemas apliquen sus actualizaciones a sus EntityManager.
             * @param dt sf::Time delta time
             */
            void update(sf::Time dt);
            /**
             * @brief Hace que todos los sistemas renderizen a las Entidades que tengan que ser renderizadas.
             *
             * Este metodo necesita ir entre sf::RenderWindow::clear() y sf::RenderWindow::display()
             *
             * @param win sf::RenderWindow &
             */
            void render(sf::RenderWindow& win);
        private:
            container systems;
    };
}
#endif // SYSTEM_MANAGER_H
