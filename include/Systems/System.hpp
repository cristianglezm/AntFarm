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

#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <string>
#include <memory>

#include <EventQueue/EventQueue.hpp>
#include <EntityManager/EntityManager.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace ant{
    /**
     * @brief Clase base para los sistemas.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class System{
        public:
            /**
             * @brief Constructor por defecto.
             */
            System();
            /**
             * @brief Constructor con los requisitos de este sistema.
             * @param req ComponentsMask::Mask
             */
            System(ComponentsMask::Mask& req);
            /**
             * @brief Constructor con los requisitos, EventQueue y EntityManager
             * @param req ComponentsMask::Mask
             * @param em std::shared_ptr<EntityManager>
             * @param eventQueue std::shared_ptr<EventQueue>
             */
            System(ComponentsMask::Mask& req,std::shared_ptr<EntityManager> em,std::shared_ptr<EventQueue> eventQueue);
            /**
             * @brief Setter para los requisitos necesarios.
             * @param req ComponentsMask::Mask
             */
            void setRequiredComponents(ComponentsMask::Mask& req);
            /**
             * @brief Getter de los requisitos para el sistema.
             */
            inline const ComponentsMask::Mask& getRequiredComponts() const noexcept{ return RequiredComponents; }
            /**
             * @brief Setter para la EventQueue
             * @param eq std::shared_ptr<EventQueue>
             */
            void setEventQueue(std::shared_ptr<EventQueue> eq);
            /**
             * @brief Getter para la EventQueue
             * @return std::shared_ptr<EventQueue>
             */
            inline std::shared_ptr<EventQueue> getEventQueue() noexcept{ return eventQueue; }
            /**
             * @brief Setter Para el nombre del sistema.
             * @param name std::string
             */
            void setName(const std::string& name);
            /**
             * @brief Getter para el nombre del sistema
             * @return std::string
             */
            inline const std::string& getName() const { return name; }
            /**
             * @brief Setter para el EntityManager
             * @param em std::shared_ptr<EntityManager>
             */
            void setEntityManager(std::shared_ptr<EntityManager> em);
            /**
             * @brief Getter para el EntityManager
             * @return std::shared_ptr<EntityManager>
             */
            inline std::shared_ptr<EntityManager> getEntityManager(){ return em; }
            /**
             * @brief Metodo abstracto para dibujar en la pantalla.
             * @param win sf::RenderWindow & referencia a la pantalla para dibujar.
             */
            virtual void render(sf::RenderWindow& win) = 0;
            /**
             * @brief Metodo abstracto para actualizar entidades.
             * @param dt sf::Time delta time para los calculos.
             */
            virtual void update(const sf::Time& dt) = 0;
            virtual ~System() = default;
        protected:
            ComponentsMask::Mask RequiredComponents;
            std::shared_ptr<EventQueue> eventQueue;
            std::shared_ptr<EntityManager> em;
            std::string name;
    };
}
#endif // SYSTEM_HPP
