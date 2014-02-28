#include <EventQueue/EventQueue.hpp>
namespace ant{
    EventQueue::EventQueue(){

    }
    Event EventQueue::front(){
        return eventQueue.front();
    }
    Event EventQueue::pop(){
        Event e = eventQueue.front();
        eventQueue.pop();
        return e;
    }
    void EventQueue::push(Event e){
        eventQueue.push(e);
    }
    EventQueue::~EventQueue(){

    }
}
