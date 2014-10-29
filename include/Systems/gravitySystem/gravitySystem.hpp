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

#ifndef GRAVITY_SYSTEM_H
#define GRAVITY_SYSTEM_H
#include <Systems/System.hpp>
#include <Components/ComponentMask.hpp>
#include <Entity/States.hpp>
namespace ant{
    /**
     * @brief Sistema para aplicar la gravedad a las entidades.
     *
     * Aplica por defecto 0.8
     *
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class gravitySystem final : public System{
        public:
            /**
             * @brief Constructor por defecto.
             */
            gravitySystem();
            /**
             * @brief Overload de constructor para configurar la gravedad directamente.
             * @param g float gravedad a aplicar.
             */
            gravitySystem(float g);
            /**
             * @brief Establece la gravedad que aplicara el sistema.
             * @param g float gravedad a aplicar.
             */
            void setGravity(float g);
            /**
             * @brief Obtiene la gravedad que aplica a las entidades.
             * @return float Gravedad que aplica.
             */
            inline const float& getGravity() const { return Gravity; }
            /**
             * @brief Metodo abstracto para actualizar entidades.
             * @param dt sf::Time delta time para los calculos.
             */
            void update(const sf::Time& dt) override;
            /**
             * @brief No hace nada.
             */
            void render(sf::RenderWindow& win) override;
            ~gravitySystem();
        private:
            float Gravity;
    };
}
#endif // GRAVITY_SYSTEM_H
