#include <Subject/Subject.hpp>

namespace ant{
    Subject::Subject(){

    }
    void Subject::addObserver(std::shared_ptr<Observer> o){
        Observers.push_back(o);
    }
    void Subject::removeObserver(std::shared_ptr<Observer> o){

    }
    void Subject::notifyObservers(std::shared_ptr<baseEvent> e){
        for(auto& o: Observers){
            o->onNotify(e);
        }
    }
    Subject::~Subject(){

    }
}
