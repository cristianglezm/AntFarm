#include <../include/EventQueueTest.hpp>
#include <iostream>
#include <EventQueue/EventQueue.hpp>
#include <utility>
#include <Utils/Utility.hpp>

bool EventQueueTest(){
    std::cout << "EventQueueTest:---------------" << std::endl;
    ant::EventQueue eventQueue;
    for(int i=0;i<10;++i){
        eventQueue.push(std::make_shared<ant::Event<int,std::string>>(i,1,"Test Event"));
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
