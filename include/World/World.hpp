#ifndef WORLD_H
#define WORLD_H
#include <Graphics.hpp>
#include <EntityManager/EntityManager.hpp>
namespace ant{
    class World{
        private:

        public:
            void update(sf::Time dt);
            void render();
    };
}
#endif // WORLD_H