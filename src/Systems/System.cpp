#include <Systems/System.hpp>
namespace ant{
    System::System(long int req):RequiredComponents(req){

    }
    System::System(){

    }
    void System::setRequiredComponents(long int req){
        RequiredComponents = req;
    }
    void System::setEventQueue(EventQueue& eq){
        this->eventQueue = eq;
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
