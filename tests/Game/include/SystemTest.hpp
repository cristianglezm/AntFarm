#ifndef SYSTEM_TEST_H
#define SYSTEM_TEST_H
#include <Systems/System.hpp>
/**
 * @brief Clase Sistema para probar System
 */
class testSystem : public ant::System{
    public:
        testSystem(long int req);
        virtual void update(sf::Time dt);
        virtual void render(sf::RenderWindow& win);
};
/**
 * @brief Comprueba que los sistemas efectuan correctamente las actualizaciones etc.
 */
bool SystemTest();
#endif // SYSTEM_TEST_H
