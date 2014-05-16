#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H
#include <Systems/System.hpp>
#include <Observer/Observer.hpp>
#include <Event/EventType.hpp>
#include <Components/ComponentMask.hpp>
#include <States/States.hpp>
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
    class movementSystem : public System, public Observer{
        public:
            /**
             * @brief Constructor por defecto.
             */
            movementSystem();
            /**
             * @brief No hace nada.
             */
            virtual void render(sf::RenderWindow& win);
            /**
             * @brief Aplica la velocidad a todas las entidades con los componentes necesarios.
             * @param dt sf::Time delta time necesario para que se muevan siempre igual sin tener en cuenta los fps.
             */
            virtual void update(sf::Time dt);
            /**
             * @brief Cuando recibe Eventos COLLISION_EVENT parara a las entidades si se mueven.
             * @param e std::shared_ptr<baseEvent> evento.
             */
            void onNotify(std::shared_ptr<baseEvent> e);
            ~movementSystem();
    };
}

#endif // MOVEMENT_SYSTEM_H
