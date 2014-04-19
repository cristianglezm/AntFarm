#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Systems/System.hpp>
#include <Components/ComponentMask.hpp>
namespace ant{
    /**
     * @brief Sistema encargado de mostrar las entidades que tengan los componentes necesarios.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class renderSystem : public System{
        public:
            /**
             * @brief Constructor por defecto.
             */
            renderSystem();
            /**
             * @brief Renderiza las Entity con los componentes Transform y Sprite, Destructable.
             * @param win sf::RenderWindow & Ventana a la cual dibujar.
             */
            virtual void render(sf::RenderWindow& win);
            /**
             * @brief No hace nada.
             */
            virtual void update(sf::Time dt);
            ~renderSystem();
    };
}
#endif // RENDER_SYSTEM_H
