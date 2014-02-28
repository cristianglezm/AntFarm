#ifndef OBSERVER_H
#define OBSERVER_H
#include <Event/Event.hpp>
namespace ant{
    class Observer{
        public:
            Observer(){};
            virtual void onNotify(Event e){};
            ~Observer(){};
    };
}
#endif // OBSERVER_H
