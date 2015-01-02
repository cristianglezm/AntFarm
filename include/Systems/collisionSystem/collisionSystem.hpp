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

#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H
#include <Systems/System.hpp>
#include <Utils/Quadtree.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Components/ComponentMask.hpp>
#include <Components/ComponentsAlias.hpp>
#include <Entity/States.hpp>
#include <Event/EventType.hpp>
#include <Utils/Math.hpp>

namespace ant{
    /**
     * @class collisionSystem
     * @brief Sistema que comprueba las colisiones entre entidades.
     *
     * Cuando detecta una colision añade un evento a la EventQueue con las dos entidades que colisionaron.
     *  -# Event<Entity*,Entity*> -> type: COLLISION_EVENT
     *  -# Event<Entity*,int> -> type: TERRAIN_COLLISION
     *  -# Event<Entity*> -> type: OUT_MAP
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class collisionSystem final : public System{
        public:
            /**
             * @brief Constructor por defecto.
             * @param bounds sf::FloatRect rectangulo del QuadTree.
             * @param GameMap sf::VertexArray * Terreno del juego.
             */
            collisionSystem(sf::FloatRect bounds,sf::VertexArray* GameMap);
            /**
             * @brief Renderiza el Quadtree si RENDER_QTREE esta definido.
             * si no no hace nada.
             */
            virtual void render(sf::RenderWindow& win) override{
                #ifdef RENDER_QTREE
                    qtree.render(win);
                #endif
            }
            /**
             * @brief Comprueba las colisiones de las entidades.
             *
             * Envia eventos de colision y eventos especificos del terreno.
             *  -# Event<Entity*,Entity*> -> type: COLLISION_EVENT
             *  -# Event<Entity*,int> -> type: TERRAIN_COLLISION
             *  -# Event<Entity*> -> type: OUT_MAP
             * @param dt sf::Time delta time
             */
            virtual void update(const sf::Time& dt) override;
            ~collisionSystem() = default;
        private:
            /**
             * @brief Comprueba si una entidad y sus bordes estan dentro del mapa.
             *
             * Envia un evento para decir por donde a colisionado la entidad con el terreno.
             *
             * 1 esquina superior izquierda -> envia evento de colision con pared 0
             * 2 esquina superior derecha -> envia evento de colision con pared 1
             * 3 esquina inferior mediana izquierda -> envia evento de colision con escalon para subirlo 2
             * 4 esquina inferior izquierda -> Cambia estado de FALLING a GROUND
             * 5 esquina inferior mediana derecha -> envia evento de colision con escalon para subirlo 2
             * 6 esquina inferior derecha -> Cambia estado de FALLING a GROUND
             *
             *  -# Event<Entity*,int> -> type: TERRAIN_COLLISION
             *
             * @param entity Entity * puntero de la entidad
             * @param eBounds sf::FloatRect bordes de la entidad
             */
            void testTerrainCollision(Entity* entity,const sf::FloatRect& eBounds);
            Utils::Quadtree qtree;
            sf::FloatRect gameBounds;
            sf::VertexArray* gameMap;
    };
}
#endif // COLLISION_SYSTEM_H
