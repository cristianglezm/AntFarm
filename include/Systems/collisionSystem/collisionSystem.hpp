#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H
#include <Systems/System.hpp>
#include <Utils/Quadtree.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Components/ComponentMask.hpp>
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
    class collisionSystem : public System{
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
            virtual void render(sf::RenderWindow& win){
                #ifdef RENDER_QTREE
                    qtree.render(win);
                #else
                    return;
                #endif
            }
            /**
             * @brief Comprueba las colisiones de las entidades.
             *
             * Envia eventos de colision y eventos especificos del suelo.
             *  -# Event<Entity*,Entity*> -> type: COLLISION_EVENT
             *  -# Event<Entity*,int> -> type: TERRAIN_COLLISION
             *  -# Event<Entity*> -> type: OUT_MAP
             * @param dt sf::Time delta time
             */
            virtual void update(sf::Time dt);
            virtual ~collisionSystem();
        private:
            /**
             * @brief Comprueba si una entidad y sus bordes estan dentro del mapa.
             *
             * Envia un evento para decir por donde a colisionado la entidad con el suelo.
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
