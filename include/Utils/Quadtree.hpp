#ifndef QUADTREE_H
#define QUADTREE_H
#include <array>
#include <memory>
#include <list>
#include <Entity/Entity.hpp>
#include <SFML/Graphics/Rect.hpp>
namespace ant{
    namespace Utils{
        class Quadtree{
            private:
                const static int MAX_CAPACITY = 10;
                const static int MAX_LEVEL = 5;
                std::array<std::unique_ptr<Quadtree>,4> nodes;
                sf::FloatRect bounds;
                std::list<Entity*> entities;
                void split();
            public:
                Quadtree();
                Quadtree(sf::FloatRect bounds);
                int getIndex(Entity* e);
                void insert(Entity* e);
                void clear();
                std::list<Entity*> retrieve(std::list<Entity*> entities,Entity* e);
                ~Quadtree();
        };
    };
};
#endif
