#include <../include/EventQueueTest.hpp>
#include <iostream>
#include <EventQueue/EventQueue.hpp>

bool EventQueueTest(){
    std::cout << "EventQueueTest:---------------" << std::endl;
    ant::EventQueue eventQueue;
    for(int i=0;i<10;++i){
        eventQueue.push(std::shared_ptr<ant::Event>(new ant::Event(i)));
    }
    std::cout << "Processing Queue..." << std::endl;
    while(!eventQueue.isEmpty()){
        std::cout << "Event type: " << eventQueue.pop()->getType() << std::endl;
    }
    if(eventQueue.isEmpty()){
        std::cout << "The Queue Is Empty" << std::endl;
    }
    return true;
}
