#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H
#include <Systems/System.hpp>
#include <Observer/Observer.hpp>

namespace ant{
    class movementSystem : public System, public Observer{
        private:

        public:
            movementSystem(long int req);
            virtual void render(sf::RenderWindow& win);
            virtual void update(sf::Time dt);
            void onNotify(std::shared_ptr<baseEvent> e);
            ~movementSystem();
    };
}

#endif // MOVEMENT_SYSTEM_H
