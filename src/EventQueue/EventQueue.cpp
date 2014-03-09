#include <EventQueue/EventQueue.hpp>
namespace ant{
    EventQueue::EventQueue(){

    }
    std::shared_ptr<Event>& EventQueue::front(){
        return eventQueue.front();
    }
    std::shared_ptr<Event> EventQueue::pop(){
        std::shared_ptr<Event> e = std::move(eventQueue.front());
        eventQueue.pop();
        return std::move(e);
    }
    void EventQueue::push(std::shared_ptr<Event> e){
        eventQueue.push(std::move(e));
    }
    EventQueue::~EventQueue(){

    }
}
