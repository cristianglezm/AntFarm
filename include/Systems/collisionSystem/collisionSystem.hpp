#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H
#include <Systems/System.hpp>
#include <Utils/Quadtree.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <Components/ComponentMask.hpp>
#include <Event/EventType.hpp>
#include <Utils/Math.hpp>

namespace ant{
    /**
     * @class collisionSystem
     * @brief Sistema que comprueba las colisiones entre entidades.
     *
     * Cuando detecta una colision añade un evento a la EventQueue con las dos entidades que colisionaron.
     * Event<Entity*,Entity*> -> type: COLLISION_EVENT
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     * @todo
     *      -# Event<Entity*> -> type: OUT_OF_MAP_EVENT
     *      -# Event<Entity*> -> type: PIXEL_COLLISION_EVENT
     */
    class collisionSystem : public System{
        public:
            /**
             * @brief Constructor por defecto.
             * @param bounds sf::FloatRect rectangulo del QuadTree.
             */
            collisionSystem(sf::FloatRect bounds);
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
             * @param dt sf::Time delta time
             */
            virtual void update(sf::Time dt);
            virtual ~collisionSystem();
        private:
            Utils::Quadtree qtree;
    };
}
#endif // COLLISION_SYSTEM_H
