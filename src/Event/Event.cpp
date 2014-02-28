#include <Event/Event.hpp>
namespace ant{
    Event::Event(int type): type(type){

    }
    void Event::setType(int type){
        this->type = type;
    }
}
