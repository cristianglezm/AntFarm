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
             * @brief devuelve el evento de colision.
             * @return Subject &
             */
            inline Subject& OnCollision(){ return onCollision; }
            /**
             * @brief Devuelve el evento de transporte.
             * @return Subject &
             */
            inline Subject& OnTransport(){ return onTransport; }
            /**
             * @brief Procesa el evento y lo envia a los observadores que esten subscritos.
             * @param e std::shared_ptr<baseEvent>
             * @return bool
             */
            bool DispatchEvent(std::shared_ptr<baseEvent> e);
            ~GameEventDispatcher();
        private:
            Subject onCollision;
            Subject onTransport;
    };
}
#endif // GAME_EVENT_DISPATCHER_H
