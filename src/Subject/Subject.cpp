#include <Subject/Subject.hpp>

namespace ant{
    Subject::Subject(){

    }
    void Subject::addObserver(Observer& o){
        Observers.push_back(o);
    }
    void Subject::removeObserver(Observer& o){

    }
    void Subject::notifyObservers(Event e){
        for(auto& o: Observers){

        }
    }
    Subject::~Subject(){

    }
}
