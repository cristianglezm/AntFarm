#include <Subject/Subject.hpp>

namespace ant{
    Subject::Subject(){

    }
    void Subject::addObserver(Observer* o){
        Observers.push_back(o);
    }
    void Subject::removeObserver(Observer* o){
        Observers.remove(o);
    }
    void Subject::notifyObservers(std::shared_ptr<baseEvent> e){
        for(auto& o: Observers){
            o->onNotify(e);
        }
    }
    Subject::~Subject(){

    }
}
