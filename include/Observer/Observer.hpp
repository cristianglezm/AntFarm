#ifndef OBSERVER_H
#define OBSERVER_H
#include <memory>
#include <Event/Event.hpp>
namespace ant{
    class Observer{
        public:
            Observer(){};
            virtual void onNotify(std::shared_ptr<Event> e){};
            ~Observer(){};
    };
}
#endif // OBSERVER_H
