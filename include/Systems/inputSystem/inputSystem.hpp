#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H
#include <Systems/System.hpp>

namespace ant{
    class inputSystem : public System{
        private:

        public:
            inputSystem();
            virtual void render(sf::RenderWindow& win);
            virtual void update(sf::Time dt);
            ~inputSystem();
    };
}

#endif // INPUT_SYSTEM_H
