#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <Systems/System.hpp>
#include <Components/ComponentMask.hpp>
namespace ant{
    class renderSystem : public System{
        private:
            std::shared_ptr<sf::RenderWindow> renderWindow;
        public:
            renderSystem();
            renderSystem(std::shared_ptr<sf::RenderWindow> rw);
            void setRenderWindow(std::shared_ptr<sf::RenderWindow> rw);
            inline std::shared_ptr<sf::RenderWindow> getRenderWindow(){ return renderWindow; }
            virtual void render();
            virtual void update(sf::Time dt);
            ~renderSystem();
    };
};
#endif // RENDER_SYSTEM_H
