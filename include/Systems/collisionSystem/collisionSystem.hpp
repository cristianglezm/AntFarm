#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H
#include <Systems/System.hpp>
#include <Utils/Quadtree.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <Components/ComponentMask.hpp>
#include <Event/EventType.hpp>

namespace ant{
    class collisionSystem : public System{
        private:
            Utils::Quadtree qtree;
        public:
            collisionSystem(long int req,sf::FloatRect bounds);
            virtual void render(sf::RenderWindow& win);
            virtual void update(sf::Time dt);
            virtual ~collisionSystem();
    };
}
#endif // COLLISION_SYSTEM_H
