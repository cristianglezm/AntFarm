#ifndef DIGGING_SYSTEM_H
#define DIGGING_SYSTEM_H
#include <Systems/System.hpp>
#include <Observer/Observer.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace ant{
    class diggingSystem : public System, Observer{
        private:
            float height;
            float width;
            sf::VertexArray* map;
        public:
            diggingSystem(long int req,sf::VertexArray map);
            virtual void onNotify(std::shared_ptr<baseEvent> e);
            virtual void render(sf::RenderWindow& win);
            virtual void update(sf::Time dt);
            ~diggingSystem();
    };
 }

#endif // DIGGING_SYSTEM_H
