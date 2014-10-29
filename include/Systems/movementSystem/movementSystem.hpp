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

#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H
#include <Systems/System.hpp>
#include <Observer/Observer.hpp>
#include <Event/EventType.hpp>
#include <Components/ComponentMask.hpp>
#include <Entity/States.hpp>
#include <Utils/Math.hpp>
namespace ant{
    /**
     * @brief Sistema encargado de hacer que las entidades se muevan.
     *
     * Las entidades se moveran si tienen el componente Velocity y Transform.
     * Se moveran segun la rotacion que tengan y la velocidad actual.
     * Maneja a las entidades segun los eventos que reciba del sistema de colision.
     * # Eventos que maneja:
     *  -# TERRAIN_COLLISION: cambiara la rotacion de las entidades
     *  -# COLLISION_EVENT: ~
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class movementSystem final: public System, public Observer{
        public:
            /**
             * @brief Constructor por defecto.
             */
            movementSystem();
            /**
             * @brief No hace nada.
             */
            void render(sf::RenderWindow& win) override;
            /**
             * @brief Aplica la velocidad a todas las entidades con los componentes necesarios.
             * @param dt sf::Time delta time necesario para que se muevan siempre igual sin tener en cuenta los fps.
             */
            void update(const sf::Time& dt) override;
            /**
             * @brief Cuando recibe Eventos COLLISION_EVENT parara a las entidades si se mueven.
             * @param e std::shared_ptr<baseEvent> evento.
             */
            void onNotify(std::shared_ptr<baseEvent> e) override;
            ~movementSystem();
    };
}

#endif // MOVEMENT_SYSTEM_H
