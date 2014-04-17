#ifndef OBSERVER_H
#define OBSERVER_H
#include <memory>
#include <Event/Event.hpp>
namespace ant{
    /**
     * @brief Interfaz para los observadores.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class Observer{
        public:
            /**
             * @brief Constructor principal.
             */
            Observer(){};
            /**
             * @brief Metodo para notificar al observador del evento.
             * @param e std::shared_ptr<baseEvent> evento.
             */
            virtual void onNotify(std::shared_ptr<baseEvent> e) = 0;
            virtual ~Observer(){};
    };
}
#endif // OBSERVER_H
