#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H
#include <Systems/System.hpp>
#include <Utils/Quadtree.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace ant{
    class collisionSystem : public System{
        private:
            QuadTree qtree;
        public:
            collisionSystem(long int req);
            virtual void render(sf::RenderWindow& win);
            virtual void update(sf::Time dt);
            ~collisionSystem();
    };
}
#endif // COLLISION_SYSTEM_H
