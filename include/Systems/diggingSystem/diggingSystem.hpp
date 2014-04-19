#ifndef DIGGING_SYSTEM_H
#define DIGGING_SYSTEM_H
#include <Systems/System.hpp>
#include <Observer/Observer.hpp>
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
             */
            diggingSystem(sf::VertexArray* map);
            /**
             *
             */
            virtual void onNotify(std::shared_ptr<baseEvent> e);
            /**
             *
             */
            virtual void render(sf::RenderWindow& win);
            /**
             *
             */
            virtual void update(sf::Time dt);
            ~diggingSystem();
        private:
            float height;
            float width;
            sf::VertexArray* map;
    };
 }

#endif // DIGGING_SYSTEM_H
