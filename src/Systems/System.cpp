#include <Systems/System.hpp>
namespace ant{
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
    System::~System(){

    }
}
