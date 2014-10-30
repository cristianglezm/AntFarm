#include <EventQueue/EventQueue.hpp>
namespace ant{
    std::shared_ptr<baseEvent>& EventQueue::front(){
        return eventQueue.front();
    }
    std::shared_ptr<baseEvent> EventQueue::pop(){
        std::shared_ptr<baseEvent> e = std::move(eventQueue.front());
        eventQueue.pop();
        return std::move(e);
    }
    void EventQueue::push(std::shared_ptr<baseEvent>&& e){
        eventQueue.push(std::move(e));
    }
    void EventQueue::clear(){
        while(!eventQueue.empty()){
            eventQueue.pop();
        }
    }
}
