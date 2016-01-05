#include <Subject/Subject.hpp>

namespace ant{
    void Subject::addObserver(Observer* o){
        Observers.emplace_back(o);
    }
    void Subject::removeObserver(Observer* o){
        Observers.erase(std::remove(Observers.begin(),Observers.end(),o),Observers.end());
    }
    void Subject::notifyObservers(std::shared_ptr<baseEvent> e){
        for(auto& o: Observers){
            o->onNotify(e);
        }
    }
}
