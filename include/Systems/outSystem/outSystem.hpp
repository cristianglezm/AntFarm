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

#ifndef OUT_SYSTEM_H
#define OUT_SYSTEM_H
#include <Systems/System.hpp>
#include <EntityFactory/EntityFactory.hpp>
#include <Observer/Observer.hpp>
#include <Event/EventType.hpp>
#include <Entity/States.hpp>
#include <Components/ComponentMask.hpp>
namespace ant{
    /**
     * @brief Sistema encargado de quitar a las entidades que chocan con las entidades con componente OUT
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class outSystem : public System, public Observer{
        public:
            /**
             * @brief Constructor por defecto.
             */
            outSystem();
            /**
             * @brief Constructor con el numero totales de entidades de este nivel.
             *
             * Este Sistema envia un evento cuando el numero de entidades del level
             *
             * @param TotalEntities int
             */
            outSystem(int TotalEntities);
            /**
             * @brief No hace nada.
             */
            void render(sf::RenderWindow& win);
            /**
             * @brief Actualiza el sistema
             *
             * Comprueba las entidades que han no tienen componentes para eliminarlas.
             *
             */
            void update(sf::Time dt);
            /**
             * @brief recibe los Out_MAP para eliminar estas entidades.
             */
            void onNotify(std::shared_ptr<baseEvent> e);
            ~outSystem();
        private:
            int totalEntities;
            int savedEntities;
    };
}
#endif // OUT_SYSTEM_H
