#ifndef SYSTEM_TEST_H
#define SYSTEM_TEST_H
#include <Systems/System.hpp>
class testSystem : public ant::System{
    public:
        testSystem(long int req);
        virtual void update(sf::Time dt);
        virtual void render(sf::RenderWindow& win);
};
bool SystemTest();
#endif // SYSTEM_TEST_H
