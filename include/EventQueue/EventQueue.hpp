#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H
#include <queue>
#include <memory>
#include <Event/Event.hpp>
namespace ant{
    /** @brief Clase donde se almacenan los eventos para
     *         ser procesados despues.
     *  @author Cristian Gonzalez Moreno <Cristian.glez.m@gmail.com>
     *  @version 0.1
     */
    class EventQueue{
        public:
            /**
             * Constructor por defecto.
             */
            EventQueue();
            /**
             * @brief Añade un evento al final de la cola.
             * @param e std::shared_ptr<baseEvent> Evento a añadir.
             */
            void push(std::shared_ptr<baseEvent> e);
            /**
             * @brief Elimina el evento de la cola y lo devuelve.
             * @return std::shared_ptr<baseEvent>
             */
            std::shared_ptr<baseEvent> pop();
            /**
             * @brief Consulta el evento que esta al frente de la cola.
             * @return std::shared_ptr<baseEvent> & referencia al evento.
             */
            std::shared_ptr<baseEvent>& front();
            /**
             * @brief Si la cola esta vacia o no.
             * @return bool
             */
            inline bool isEmpty(){ return eventQueue.empty(); }
            /**
             * @brief Devuelve el numero de eventos en la cola.
             * @return int
             */
            inline int size(){ return eventQueue.size(); }
            /**
             * @brief limpia la cola.
             */
            void clear();
            ~EventQueue();
        private:
            std::queue<std::shared_ptr<baseEvent>> eventQueue;
    };
}
#endif // EVENT_QUEUE_H
