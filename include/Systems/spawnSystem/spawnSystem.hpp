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

#ifndef SPAWN_SYSTEM_HPP
#define SPAWN_SYSTEM_HPP

#include <Systems/System.hpp>
#include <Observer/Observer.hpp>
#include <Event/EventType.hpp>
#include <EntityFactory/EntityFactory.hpp>
#include <Entity/States.hpp>
#include <Config.hpp>

namespace ant{
    /**
     * @brief Sistema encargado de crear las entidades sobre el tiempo establecido.
     *
     * Crea las entidades en la posicion de las entidades con ComponentsMask::COMPONENT_IN.
     *
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class spawnSystem final : public System, public Observer{
        public:
            /**
             * @brief constructor por defecto.
             * @param nEntities int numero de entidades a crear.
             * @param ot sf::Time Tiempo para crear las entidades cada X tiempo.
             * @param ef EntityFactory * Para crear las entidades.
             * @param spawnPoint sf::Vector2f sitio donde saldran las entidades.
             * @param state long int Estados iniciales para cuando las entidades son creadas.
             */
            spawnSystem(int nEntities, EntityFactory* ef,sf::Time ot,sf::Vector2f spawnPoint,long int state);
            /**
             * @brief Establece el estado por defecto que pondra a las entidades.
             * @param state long int estados de las entidades
             * @code
             *  setStates(States::FALLING | STATES::ONFIRE);
             * @endcode
             */
            void setStates(long int state);
            /**
             * @brief Obtiene los estados que pone por defecto al crear las entidades.
             * @return long int
             */
            inline const long& getStates() const { return states; }
            /**
             * @brief Cada x segundos crea un entidad en el sitio establecido.
             * @param dt sf::Time delta time
             */
            virtual void update(const sf::Time& dt) override;
            /**
             * @brief no hace nada.
             */
            virtual void render(sf::RenderWindow& win) override;
            /**
             * @brief Recibe eventos para cambiar el tiempo
             * o el numero de entidades que tiene que crear.
             * @param e std::shared_ptr<baseEvent>
             */
            virtual void onNotify(std::shared_ptr<baseEvent> e) override;
            ~spawnSystem() = default;
        private:
            EntityFactory* entityFactory;
            int nEntities;
            int createdEntities;
            sf::Time overTime;
            sf::Time elapsedTime;
            sf::Vector2f spawnPoint;
            sf::Clock clock;
            long int states;
            ComponentSettings cs;
    };
}
#endif // SPAWN_SYSTEM_H
