#ifndef GAME_EVENT_DISPATCHER_H
#define GAME_EVENT_DISPATCHER_H
#include <Event/Event.hpp>
#include <Event/EventType.hpp>
#include <Subject/Subject.hpp>
namespace ant{
    /**
     * @brief Clase encargada de processar eventos.
     *
     * Esta clase contiene a los eventos a los cuales
     * se pueden suscribir los observadores.
     *
     * @author Cristian Gonzalez Moreno <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class GameEventDispatcher{
        public:
            /**
             * @brief Constructor por defecto.
             */
            GameEventDispatcher();
            /**
             * @brief lista de observadores del evento onCollision.
             */
            Subject onCollision;
            /**
             * @brief Eventos para el sistema de creacion de entidades.
             */
            Subject spawnEvents;
            /**
             * @brief Procesa el evento y lo envia a los observadores que esten subscritos.
             * @param e std::shared_ptr<baseEvent>
             * @return bool
             */
            bool DispatchEvent(std::shared_ptr<baseEvent> e);
            ~GameEventDispatcher();
    };
}
#endif // GAME_EVENT_DISPATCHER_H
