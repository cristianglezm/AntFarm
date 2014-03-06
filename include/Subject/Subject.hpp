#ifndef SUBJECT_H
#define SUBJECT_H
#include <list>
#include <Observer/Observer.hpp>
namespace ant{
    class Subject{
        private:
            std::list<std::shared_ptr<Observer> > Observers;
        public:
            Subject();
            void addObserver(std::shared_ptr<Observer> o);
            void removeObserver(std::shared_ptr<Observer> o);
            void notifyObservers(std::unique_ptr<Event> e);
            ~Subject();
    };
}
#endif // SUBJECT_H
