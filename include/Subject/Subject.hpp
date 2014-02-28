#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <Observer/Observer.hpp>
namespace ant{
    class Subject{
        private:
            std::vector<Observer> Observers;
        public:
            Subject();
            void addObserver(Observer& o);
            void removeObserver(Observer& o);
            void notifyObservers(Event e);
            ~Subject();
    };
}
#endif // SUBJECT_H
