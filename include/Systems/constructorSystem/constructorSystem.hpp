#ifndef CONSTRUCTION_SYSTEM_H
#define CONSTRUCTION_SYSTEM_H
#include <Systems/System.hpp>
#include <Observer/Observer.hpp>
#include <Components/ComponentMask.hpp>
#include <EntityFactory/EntityFactory.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace ant{
    /**
     * @brief Sistema encargado de que las hormigas construyan etc.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class constructionSystem : public System, public Observer{
        public:
            /**
             * @brief Constructor por defecto.
             * @param map sf::VertexArray * Destructable para construir, etc.
             * @param boundsMap sf::FloatRect bordes del destructable.
             */
            constructionSystem(sf::VertexArray* map,sf::FloatRect boundsMap);
            /**
             *
             */
            virtual void onNotify(std::shared_ptr<baseEvent> e);
            /**
             * @brief No hace nada.
             */
            virtual void render(sf::RenderWindow& win);
            /**
             * @brief Gestiona la construccion de los elementos.
             * @param dt sf::Time delta time
             */
            virtual void update(sf::Time dt);
            ~constructionSystem();
        private:
            sf::FloatRect boundsMap;
            sf::VertexArray* map;
            EntityFactory * entityFactory;
    };
 }

#endif // CONSTRUCTION_SYSTEM_H
