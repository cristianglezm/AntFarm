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

#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Systems/System.hpp>
#include <Components/ComponentMask.hpp>
namespace ant{
    /**
     * @brief Sistema encargado de mostrar las entidades que tengan los componentes necesarios.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class renderSystem final : public System{
        public:
            /**
             * @brief Constructor por defecto.
             */
            renderSystem();
            /**
             * @brief Renderiza las Entity con los componentes Transform y Sprite, Destructable.
             * @param win sf::RenderWindow & Ventana a la cual dibujar.
             */
            void render(sf::RenderWindow& win) override;
            /**
             * @brief No hace nada.
             */
            void update(const sf::Time& dt) override;
            ~renderSystem();
    };
}
#endif // RENDER_SYSTEM_H
