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
        private:
            std::queue<std::shared_ptr<Event> > eventQueue;
        public:
            EventQueue();
            void push(std::shared_ptr<Event> e);
            std::shared_ptr<Event> pop();
            std::shared_ptr<Event>& front();
            inline bool isEmpty(){ return eventQueue.empty(); }
            ~EventQueue();
    };
}
#endif // EVENT_QUEUE_H
