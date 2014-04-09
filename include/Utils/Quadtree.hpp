#ifndef QUADTREE_H
#define QUADTREE_H
#include <array>
#include <memory>
#include <list>
#include <Entity/Entity.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>

namespace ant{
    namespace Utils{
        class Quadtree{
            private:
                const static int MAX_CAPACITY = 100;
                const static int MAX_LEVEL = 1000;
                int level;
                std::array<std::unique_ptr<Quadtree>,4> nodes;
                sf::FloatRect bounds;
                std::list<Entity*> entities;
                void split();
                int getIndex(Entity* e);
            public:
                typedef std::list<Entity*> list;
                Quadtree(int level);
                Quadtree(int level,sf::FloatRect bounds);
                Quadtree(sf::FloatRect bounds);
                void insert(Entity* e);
                void clear();
                std::list<Entity*> retrieve(std::list<Entity*>& entities,Entity* e);
                void render(sf::RenderWindow& win);
                ~Quadtree();
        };
    }
}
#endif
