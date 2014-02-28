#include <../include/EventQueueTest.hpp>
#include <iostream>
#include <EventQueue/EventQueue.hpp>

bool EventQueueTest(){
    std::cout << "EventQueueTest:---------------" << std::endl;
    ant::EventQueue eventQueue;
    for(int i=0;i<10;++i){
        eventQueue.push(ant::Event(i));
    }
    std::cout << "Processing Queue..." << std::endl;
    while(!eventQueue.isEmpty()){
        std::cout << "Event: " << eventQueue.pop().getType() << std::endl;
    }
    if(eventQueue.isEmpty()){
        std::cout << "The Queue Is Empty" << std::endl;
    }
}
