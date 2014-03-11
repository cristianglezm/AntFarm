#include <Systems/System.hpp>
namespace ant{
    System::System(){
        em.reset(new EntityManager());
        eventQueue.reset(new EventQueue());
    }
    System::System(long int req):RequiredComponents(req){
        em.reset(new EntityManager());
        eventQueue.reset(new EventQueue());
    }
    System::System(long int req,std::shared_ptr<EntityManager> em,std::shared_ptr<EventQueue> eventQueue){
        this->em = em;
        this->eventQueue = eventQueue;
        this->RequiredComponents = req;
    }
    void System::setRequiredComponents(long int req){
        RequiredComponents = req;
    }
    void System::setEventQueue(std::shared_ptr<EventQueue> eventQueue){
        this->eventQueue = eventQueue;
    }
    void System::setName(std::string name){
        this->name = name;
    }
    void System::setEntityManager(std::shared_ptr<EntityManager> em){
        this->em = em;
    }
    System::~System(){

    }
}
