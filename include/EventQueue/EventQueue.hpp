#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H
#include <queue>
#include <Event/Event.hpp>
namespace ant{
    class EventQueue{
        private:
            std::queue<Event> eventQueue;
        public:
            EventQueue();
            void push(Event e);
            Event pop();
            Event front();
            inline bool isEmpty(){ return eventQueue.empty(); }
            ~EventQueue();
    };
}
#endif // EVENT_QUEUE_H
