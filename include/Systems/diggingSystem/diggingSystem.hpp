#ifndef DIGGING_SYSTEM_H
#define DIGGING_SYSTEM_H
#include <Systems/System.hpp>
#include <Observer/Observer.hpp>
#include <Components/ComponentMask.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace ant{
    /**
     * @brief Sistema encargado de que las hormigas cojan la tierra etc.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class diggingSystem : public System, Observer{
        public:
            /**
             * @brief Constructor por defecto.
             * @param map sf::VertexArray * Destructable para destruir.
             * @param boundsMap sf::FloatRect bordes del destructable.
             */
            diggingSystem(sf::VertexArray* map,sf::FloatRect boundsMap);
            /**
             *
             */
            virtual void onNotify(std::shared_ptr<baseEvent> e);
            /**
             * @brief Renderiza las particulas de tierra que lleven las hormigas.
             * @param win & sf::RenderWindow Ventana a la cual dibujar.
             */
            virtual void render(sf::RenderWindow& win);
            /**
             * @brief Actualiza la posicion de las hormigas que lleven tierra.
             *
             * Gestiona el coger y dejar tierra de las hormigas.
             *
             * @param dt sf::Time delta time
             */
            virtual void update(sf::Time dt);
            ~diggingSystem();
        private:
            sf::FloatRect boundsMap;
            sf::VertexArray* map;
    };
 }

#endif // DIGGING_SYSTEM_H
