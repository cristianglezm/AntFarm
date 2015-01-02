#include <Systems/System.hpp>
namespace ant{
    System::System()
    : RequiredComponents(0)
    , eventQueue(std::make_shared<EventQueue>())
    , em(std::make_shared<EntityManager>()){}
    System::System(long int req)
    : RequiredComponents(req)
    , eventQueue(std::make_shared<EventQueue>())
    , em(std::make_shared<EntityManager>()){}
    System::System(long int req,std::shared_ptr<EntityManager> em,std::shared_ptr<EventQueue> eventQueue)
    : RequiredComponents(req)
    , eventQueue(eventQueue)
    , em(em){}
    void System::setRequiredComponents(long int req){
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
