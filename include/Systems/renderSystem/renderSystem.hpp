#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Systems/System.hpp>
#include <Components/ComponentMask.hpp>
namespace ant{
    class renderSystem : public System{
        private:
        public:
            renderSystem(long int req);
            virtual void render(sf::RenderWindow& win);
            virtual void update(sf::Time dt);
            ~renderSystem();
    };
};
#endif // RENDER_SYSTEM_H
