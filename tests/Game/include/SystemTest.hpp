#ifndef SYSTEM_TEST_H
#define SYSTEM_TEST_H
#include <Systems/System.hpp>
class testSystem : public ant::System{
    public:
        testSystem(long int req);
        virtual void update(sf::Time dt);
        virtual void render();
};
bool SystemTest();
#endif // SYSTEM_TEST_H
