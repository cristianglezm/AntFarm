#include <Systems/System.hpp>

namespace ant{
    System::System()
    : RequiredComponents(0) // ComponentsMask::COMPONENT_NONE
    , eventQueue(std::make_shared<EventQueue>())
    , em(std::make_shared<EntityManager>())
    , name("baseSystem"){}
    System::System(ComponentsMask::Mask& req)
    : RequiredComponents(req)
    , eventQueue(std::make_shared<EventQueue>())
    , em(std::make_shared<EntityManager>())
    , name("baseSystem"){}
    System::System(ComponentsMask::Mask& req,std::shared_ptr<EntityManager> em, std::shared_ptr<EventQueue> eventQueue)
    : RequiredComponents(req)
    , eventQueue(eventQueue)
    , em(em)
    , name("baseSystem"){}
    void System::setRequiredComponents(ComponentsMask::Mask& req){
        RequiredComponents = req;
    }
    void System::setEventQueue(std::shared_ptr<EventQueue> eventQueue){
        this->eventQueue = eventQueue;
    }
    void System::setName(const std::string& name){
        this->name = name;
    }
    void System::setEntityManager(std::shared_ptr<EntityManager> em){
        this->em = em;
    }
}
